#include "../mem/pmm.h"
#include "../mem/kmalloc.h"
#include "../util/alias.h"
#include "proc.h"
#include "test/test.h"

#define PROCS_MAX 255

static ushort id_count = 0;
static ushort current_proc_id = 0;

// TODO: a better implementation
struct proc procs[2]; // because id is ushort

void proc_tmp_setup()
{
	procs[0] = proc_create(PROC_READY, &foo, 5000);
	procs[1] = proc_create(PROC_READY, &fizz, 5000);
}

struct proc proc_create(state_t state, virt_t ptr, size_t stack_size)
{
	struct proc proc;

	proc.id = id_count;
	id_count++;

	proc.state = state;

	proc.ctx.gp = (struct gp_regs) {0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	proc.ctx.hw.rsp = vmalloc(stack_size) + stack_size;
	proc.ctx.hw.rip = ptr;
	proc.ctx.hw.rflags = (size_t) 0x202;

	return proc;
}

void proc_kill(ushort id)
{
	procs[id].state = PROC_DEAD;
}

void proc_save(struct int_frame *ctx)
{
	procs[current_proc_id].ctx = *ctx;
}

void proc_exit(int retvalue)
{
	if (!retvalue)
		print_line(" SUCESS!\n");
	procs[current_proc_id].state = PROC_DEAD;
}

void proc_suspend(ushort id)
{
	procs[id].state = PROC_READY;
}

void proc_switch(struct int_frame *ctx)
{
	procs[current_proc_id].ctx = *ctx;
	procs[current_proc_id].state = PROC_READY;
}
static bool defined = false;

struct proc *proc_sched(struct int_frame *intf)
{
	if (defined) {
		procs[current_proc_id].ctx = *intf;
		//print_hex((uint64_t)procs[current_proc_id].ctx.rip);
		//print_hex((uint64_t)procs[current_proc_id].ctx.rsp);
	} else defined = true;
	if (current_proc_id == 0)
		current_proc_id = 1;
	else 
		current_proc_id = 0;

	//print_line("Gol da alemanha!\n");
	return &procs[current_proc_id];
}
