#ifndef ARCH_AMD64_GDT_H
#define ARCH_AMD64_GDT_H

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t gdt_entry_t;

bool gdt_init();

#endif // ARCH_AMD64_GDT_H
