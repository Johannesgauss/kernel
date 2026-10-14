#ifndef ARCH_AMD64_IDT_H
#define ARCH_AMD64_IDT_H

#include <stdint.h>
#include <stdbool.h>

#define IDT_MAX_GATES 256


#define PIC1_COMMAND 0x20                                                
#define PIC1_DATA    0x21                                                
#define PIC2_COMMAND 0xA0                                                
#define PIC2_DATA    0xA1                                                
								     
#define PIC_EOI      0x20                                                

struct gp_regs {
	uint64_t rax;
	uint64_t rbx;
	uint64_t rcx;
	uint64_t rdx;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t r8;
	uint64_t r9;
	uint64_t r10;
	uint64_t r11;
	uint64_t r12;
	uint64_t r13;
	uint64_t r14;
	uint64_t r15;
};

struct hw_frame {
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
};

struct idt_stack_call {
	struct gp_regs regs;
	uint64_t origin;
	uint64_t err_code;
	struct hw_frame hw;
};

static inline bool is_interrupt(struct idt_stack_call *call)
{
	return (int64_t)call->origin < 0;
}

static inline uint64_t get_vector(struct idt_stack_call *call)
{
	return ~call->origin;
}

static inline uint64_t get_syscall_nr(struct idt_stack_call *call)
{
	return call->origin;
}

bool idt_init();
void irqr_add(int irqr, void (*handler)(void));

#endif // ARCH_AMD64_IDT_H
