#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <stdbool.h>
#include "util/panic.h"
#include "pmm.h"
#include "util/alias.h"

#define HHDM_OFFSET 0XFFFF800000000000

// TODO: Substitute the linked list by a tree. Way more efficient!

struct memllist_t {
	struct memllist_t *prev;
	struct memllist_t *next;
	size_t length;
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request
memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST_ID,
	.revision = 0
};
static struct memllist_t *s_head;

static inline struct memllist_t *pmm_handler(struct memllist_t *current, virt_t base_addr, size_t length)
{
	struct memllist_t *node = (struct memllist_t*) base_addr;
	node->prev = current;
	node->next = NULL;
	current->next = node;
	node->length = length;

	return node;
}

static struct memllist_t *pmm_memget_limine()
{
	struct memllist_t header = {.prev = &header, .next = &header, .length = 0};
	struct memllist_t *tail = &header;

	if (memmap_request.response == NULL) {
		// throws a kernel panic
		panic("[ FATAL ] Memory map not given by bootloader.");
	}

	struct limine_memmap_response *lmemmap = memmap_request.response;
	phy_t entry_count = lmemmap->entry_count;

	for (phy_t i = 0; i < entry_count; i++) {
		struct limine_memmap_entry *entry = lmemmap->entries[i];

		if (entry->type == LIMINE_MEMMAP_USABLE) {
			tail = pmm_handler(tail, phy_to_virt(entry->base), entry->length);
		}
	}

	header.next->prev = NULL;
	return header.next;
}

#define pmm_memget() pmm_memget_limine()

bool pmm_init()
{
	if (!(s_head = pmm_memget())) {
		panic("Out of Memory!");
	};
	return true;
}

#define PAGE_SIZE 4096
// first fit
virt_t pmm_alloc()
{
	struct memllist_t *current = s_head;
	while (current) {
		if (current->length < PAGE_SIZE)
			current = current->next;
		else
			goto EXIT;
	}
	panic("[ FATAL ] OOM: Out of Memory!");
EXIT:
	if (current->length >= PAGE_SIZE + sizeof(*current)) {
		current->length -= (uintptr_t)PAGE_SIZE;
		return (virt_t)((uintptr_t)current + current->length);
	} else {
		if (current->prev)
			current->prev->next = current->next;
		else
			s_head = current->next;
		if (current->next)
			current->next->prev = current->prev;
		return  (virt_t) current;
	}
}

void pmm_free(virt_t addr)
{
	struct memllist_t *current = s_head;
	struct memllist_t *new = (struct memllist_t *) addr;
	new->length = PAGE_SIZE;
	if (addr < (virt_t)s_head) {
		s_head->prev = new;
		new->next = s_head;
		new->prev = NULL;
		s_head = new;
		return;
	}
	while (current) {
		if ((virt_t)current <= addr && (!current->next || addr <= (virt_t)current->next))
			goto EXIT;
		current = current->next;
	}
	panic("[ FATAL ] ATTEMPT TO FREE A NON ALLOCATED PAGE!");
EXIT:;
	new->prev = current;
	if (current->next) {
		new->next = current->next;
		new->next->prev = new;
	} else {
		new->next = NULL;
	}
	current->next = new;
}
