#ifndef SCHED_PROC
#define SCHED_PROC

#include "../arch/sched/proc_ctx.h"
#include "../util/alias.h"

typedef enum {
	PROC_DEAD = 0,
	PROC_EXEC,
	PROC_BLOCK,
	PROC_WAIT
} state_t;

struct proc {
	utiny id;
	ushort father_id;
	ushort group_id;
	state_t state;
	struct proc_arch_ctx ctx;
	utiny priority;
};

struct proc proc_create(ushort id, ushort father_id, ushort group_id, state_t state, struct proc_arch_ctx ctx, utiny priority);

void proc_kill(ushort id);
void proc_exit(ushort id);

#endif SCHED_PROC
