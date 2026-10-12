#ifndef ARCH_AMD64_GDT_H
#define ARCH_AMD64_GDT_H

#include <stdint.h>
#include <stdbool.h>

#define GDT_CODE_KERNEL 0xA09A
#define GDT_DATA_KERNEL 0xA092
#define GDT_CODE_USER   0xA0FA
#define GDT_DATA_USER   0xA0F2

#define GDT_OFFSET_KERNEL_CODE 0x08
#define GDT_OFFSET_KERNEL_DATA 0x10
#define GDT_OFFSET_USER_CODE   0x18
#define GDT_OFFSET_USER_DATA   0x20

typedef uint64_t gdt_entry_t;

bool gdt_init();

#endif // ARCH_AMD64_GDT_H
