#ifndef ARCH_AMD64_VMM
#define ARCH_AMD64_VMM
#include <stdint.h>
#include <stdbool.h>

static uint64_t *pml4;
void vmm_map(void *addr);

bool vmm_init();

// TODO a better vmm_free
void vmm_free(void *addr);

#endif // ARCH_AMD64_VMM
