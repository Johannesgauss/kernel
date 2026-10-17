#include "../mem/pmm.h"
#include <stdint.h>
#include "util/memory.h"

#define PAGE_ENTRIES 512

static uint64_t *pml4;

#define SET_P    1ULL
#define SET_RW  (1ULL << 1)
#define SET_US  (1ULL << 2)
#define SET_PWT (1ULL << 3)
#define SET_PCD   (1ULL << 4)
#define SET_A (1ULL << 5)
#define SET_IGN (1ULL << 6)
#define SET_MBZ (0 << 7) | (0 << 8)
//#define SET_ADDR(entry) entry << 12
#define SET_NX  (1ULL << 63)
#define GET_PHY_ADDR (0x000FFFFFFFFFF000ULL)

static inline void pgtotable(void *page)
{
	memset(page, 0, PAGE_SIZE);
}

void vmm_map(void *addr)
{
	// 9 9 9 9 12 = 48
	uint64_t pml4_offset = (uint64_t) ((uint64_t)addr >> (9 + 9 + 9 + 12)) & 0x1FF;
	uint64_t pdpt_offset = (uint64_t) ((uint64_t)addr >> (9 + 9 + 12)) & 0x1FF;
	uint64_t pd_offset = (uint64_t) ((uint64_t)addr >> (9 + 12)) & 0x1FF;
	uint64_t pt_offset = (uint64_t) ((uint64_t)addr >> 12) & 0x1FF;

	uint64_t *pdpt;
	uint64_t *pd;
	uint64_t *pt;
//	uint64_t *page;

	// TODO: Of course, it's not a great idea all pages having US bit on. Change it later!
	if (!(pml4[pml4_offset] & SET_P)) {
		void *new_page = pmm_alloc();
		pgtotable(new_page);
		pml4[pml4_offset] = virt_to_phy((uint64_t)new_page) | SET_P | SET_RW | SET_US;
	}
	pdpt = phy_to_virt((pml4[pml4_offset] & GET_PHY_ADDR));
	if (!(pdpt[pdpt_offset] & SET_P)) {
		void *new_page = pmm_alloc();
		pgtotable(new_page);
		pdpt[pdpt_offset] = virt_to_phy((uint64_t)new_page) | SET_P | SET_RW | SET_US ;
	}
	pd = phy_to_virt((pdpt[pdpt_offset] & GET_PHY_ADDR));
	if (!(pd[pd_offset] & SET_P)) {
		void *new_page = pmm_alloc();
		pgtotable(new_page);
		pd[pd_offset] = virt_to_phy((uint64_t)new_page) | SET_P | SET_RW | SET_US;
	}
	pt = phy_to_virt((pd[pd_offset] & GET_PHY_ADDR));
	if (!(pt[pt_offset] & SET_P)) {
		void *new_page = pmm_alloc();
		pgtotable(new_page);
		pt[pt_offset] = virt_to_phy((uint64_t)new_page) | SET_P | SET_RW | SET_US;
	}
	//page = phy_to_virt((pt[pt_offset] & GET_PHY_ADDR));
}

// TODO: copy the cr3 to a new one instead
bool vmm_init()
{
	void *cr3;
	asm volatile ("mov %%cr3, %0;" : "=r"(cr3) ::);
	uint64_t *pml4_old = phy_to_virt((uint64_t) cr3 & GET_PHY_ADDR);
	pml4 = pmm_alloc();
	for (int i = 256; i < 512; i++) {
		if (pml4_old[i] & SET_P)
			pml4[i] = pml4_old[i];
	}
	asm volatile ("mov %0, %%cr3;" :: "r"(virt_to_phy((uint64_t)pml4)) :);
	pmm_free(pml4_old);
	/**/
	return true;
}

// TODO a better vmm_free
void vmm_free(void *addr)
{
	
	uint64_t pml4_offset = (uint64_t) ((uint64_t)addr >> (9 + 9 + 9 + 12)) & 0x1FF;
	uint64_t pdpt_offset = (uint64_t) ((uint64_t)addr >> (9 + 9 + 12)) & 0x1FF;
	uint64_t pd_offset = (uint64_t) ((uint64_t)addr >> (9 + 12)) & 0x1FF;
	uint64_t pt_offset = (uint64_t) ((uint64_t)addr >> 12) & 0x1FF;

	uint64_t *pdpt;
	uint64_t *pd;
	uint64_t *pt;
	uint64_t *page;

	if (!(pml4[pml4_offset] & SET_P)) goto PANIC;
	pdpt = phy_to_virt((pml4[pml4_offset] & GET_PHY_ADDR));

	if (!(pdpt[pdpt_offset] & SET_P)) goto PANIC;
	pd = phy_to_virt((pdpt[pdpt_offset] & GET_PHY_ADDR));

	if (!(pd[pd_offset] & SET_P)) goto PANIC;
	pt = phy_to_virt((pd[pd_offset] & GET_PHY_ADDR));

	if (!(pt[pt_offset] & SET_P)) goto PANIC;
	pmm_free(phy_to_virt(pt[pt_offset] & GET_PHY_ADDR));

	pt[pt_offset] = 0;
	asm volatile ("invlpg (\%0);" :: "r"(addr) : "memory");

	return;
PANIC:
		panic("[ FATAL ] ATTEMPT TO FREE A NON ALLOCATED PAGE!");
}
