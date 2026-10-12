#ifndef MEM_KMALLOC_H
#define MEM_KMALLOC_H

#include "arch/vmm.h"
#include "pmm.h"

virt_t kmalloc(size_t size);
void kfree(virt_t addr);
virt_t vmalloc(size_t size);
void vfree(virt_t addr);

#endif // MEM_KMALLOC_H
