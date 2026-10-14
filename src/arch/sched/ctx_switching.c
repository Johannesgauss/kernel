//#include "../../sched/proc.c"
#include "../gdt.h"
#include "../idt.h"
#include "proc_ctx.h"
#include "../irq.h"
#include "../../drivers/clk/clk.h"
#include "../../drivers/port.h"
#include "drivers/gfx/print_text.h"
#include "../../sched/proc.h"

extern void sched_interruption();
extern void ctx_load(void *pointer, void *stack);

struct ret
{
	void *rip;
	void *rsp;
};


int foo()
{
	print_line("I'm foo!\n");
	while (1) {

	}
	//for (uint64_t i = 0; i < 0xFFFFFFF; i++) {
	//	asm volatile ("nop");
		//asm volatile ("cli; hlt");
	//}

	//asm volatile ("sti");
	//while (1) { asm volatile ("cli; hlt"); }
	return 1;
}

// TODO: tmp name

void interruption_handler()
{
	void *rip, *rsp;

	rip = &foo;
	asm volatile ("lea proc_suspend(%%rip), %%rax" :::);
	asm volatile ("push %%rax" :::);
	asm volatile ("mov %%rsp, %0" : "=r"(rsp) :);

	outb(PIC1_COMMAND, PIC_EOI);
	ctx_load(rip, rsp);
}
