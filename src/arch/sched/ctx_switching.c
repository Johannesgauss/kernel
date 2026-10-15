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

// TODO: tmp name
static uint64_t tmp_stack[5000];

void interruption_handler()
{
	struct proc next = proc_sched();
	outb(PIC1_COMMAND, PIC_EOI);
	ctx_load(next.ctx.rip, next.ctx.rsp);
}

extern void sys_exit();
void idt_syscall(int code)
{
	//if (code == 0) {
		sys_exit();
	//}
}
