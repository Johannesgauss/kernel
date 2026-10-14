#include "../mem/pmm.h"
#include "../arch/sched/proc_ctx.h"
#include "../util/alias.h"

#define PROCS_MAX 255

typedef enum {
	PROC_DEAD = 0,
	PROC_EXEC,
	PROC_BLOCK,
	PROC_READY
} state_t;

struct proc {
	utiny id;
	ushort father_id;
	ushort group_id;
	state_t state;
	struct proc_arch_ctx ctx;
	utiny priority;
};


static ushort id_count = 0;
static ushort current_proc_id;

// TODO: a better implementation
struct proc procs[sizeof(utiny)]; // because id is ushort

struct proc proc_create(ushort id, ushort father_id, ushort group_id, state_t state, struct proc_arch_ctx ctx, utiny priority)
{
	struct proc proc;

	proc.id = id_count;
	id_count++;

	proc.father_id = father_id;
	proc.group_id = group_id;
	proc.state = state;
	proc.ctx = ctx;
	proc.priority = priority;

	return proc;
}

void proc_kill(ushort id)
{
	procs[id].state = PROC_DEAD;
}

void proc_save(struct proc_arch_ctx *ctx)
{
	procs[current_proc_id].ctx = *ctx;
}

void proc_exit(ushort id)
{
	procs[id].state = PROC_DEAD;
}

void proc_suspend(ushort id)
{
	procs[id].state = PROC_READY;
}

void proc_switch(struct proc_arch_ctx *ctx)
{
	procs[current_proc_id].ctx = *ctx;
	procs[current_proc_id].state = PROC_READY;
}
