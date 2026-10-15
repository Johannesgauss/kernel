#include "../idt.h"
#include "proc_ctx.h"
#include "../../drivers/port.h"
//#include "drivers/gfx/print_text.h"
#include "../../sched/proc.h"

extern void ctx_load(void *pointer, void *stack);

// TODO: tmp name
void interruption_handler()
{
	struct proc next = proc_sched();
	outb(PIC1_COMMAND, PIC_EOI);
	ctx_load(next.ctx.rip, next.ctx.rsp);
}
