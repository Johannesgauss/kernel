/*
#include "../idt.h"
#include "proc_ctx.h"
#include "../../drivers/port.h"
//#include "drivers/gfx/print_text.h"
#include "../../sched/proc.h"
#include "drivers/clk/pit_defs.h"

extern void ctx_load(void *ptr, void *st);

// TODO: tmp name
void interruption_handler(struct hw_frame *hf)
{
	struct hw_frame proc_hf = *hf;

	struct proc *next = proc_sched(proc_hf);
	outb(PIC1_COMMAND, PIC_EOI);
	ctx_load(next->ctx.rip, next->ctx.rsp);
} */
