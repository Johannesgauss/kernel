#include "../../sched/proc.c"
#include "../gdt.h"
#include "../idt.h"
#include "proc_ctx.h"
#include "../irq.h"
#include "../../drivers/clk/clk.h"

extern void ctx_load(void *rip, void *rsp);

// TODO: tmp name
//void timer_inter_add() { irq_routines[0] = proc_switch; }
