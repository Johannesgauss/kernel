//#include "../../sched/proc.c"
#include "../gdt.h"
#include "../idt.h"
#include "proc_ctx.h"
#include "../irq.h"
#include "../../drivers/clk/clk.h"
#include "../../drivers/port.h"
#include "drivers/gfx/print_text.h"

extern void sched_interruption();
extern void ctx_load(void *pointer, void *stack);

struct ret
{
	void *rip;
	void *rsp;
};

void interruption_handler()
{
	struct ret r;
	asm volatile ("lea foo(%%rip), %0" : "=r"(r.rip) :);
	asm volatile ("lea sched_interruption(%%rip), %%rax" :::);
	asm volatile("push %%rax" :::);
	asm volatile ("mov %%rsp, %0" : "=r"(r.rsp) :);

	print_line("Hello!\n");
	ctx_load(r.rip, r.rsp);


	outb(PIC1_COMMAND, PIC_EOI);

}

int foo()
{
//	print_line("I'm foo!\n");
	for (uint64_t i = 0; i < 0xFFFFFFFF; i++) {
		asm volatile ("nop");
		//asm volatile ("cli; hlt");
	}

	//asm volatile ("sti");
	//while (1) { asm volatile ("cli; hlt"); }
	return 1;
}

// TODO: tmp name
