#include "../mem/pmm.h"
#include "../mem/kmalloc.h"
#include "../util/alias.h"
#include "proc.h"
#include "test/test.h"

#define PROCS_MAX 255


static ushort id_count = 0;
static ushort current_proc_id = 0;

static uint64_t stack[5000];
static uint64_t stack2[5000];

struct proc proc_create(state_t state, struct int_frame ctx);
// TODO: a better implementation
struct proc procs[2]; // because id is ushort

void proc_tmp_setup()
{
	void *rsp = vmalloc(5000) - 5000;
	void *rsp2 = vmalloc(5000) - 5000;
	struct hw_frame hf;
	struct int_frame if1 = {
		{0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ (uint64_t)&foo, 0, 0, (uint64_t)stack+500, 0}
	};
	struct int_frame if2 = {
		{0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
		{ (uint64_t)&fizz, 0, 0, (uint64_t)stack2+500, 0}
	};
	procs[0] = proc_create( PROC_READY, if1);
	procs[1] = proc_create( PROC_READY, if2);
}

struct proc proc_create(state_t state, struct int_frame ctx)
{
	struct proc proc;

	proc.id = id_count;
	id_count++;

	proc.state = state;
	proc.ctx = ctx;

	proc.ctx.hw.rsp = (phy_t)vmalloc(5000) - 5000;

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
