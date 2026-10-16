#ifndef SCHED_PROC
#define SCHED_PROC

#include "../util/alias.h"
#include "../arch/idt.h"

typedef enum {
	PROC_DEAD = 0,
	PROC_EXEC = 1,
	PROC_BLOCK = 2,
	PROC_READY = 3
} state_t;

struct proc {
	struct int_frame ctx;
	state_t state;
	utiny id;
};

struct proc proc_create(state_t state, struct int_frame ctx);

void proc_kill(ushort id);
void proc_exit(int retvalue);
struct proc *proc_sched(struct int_frame *hf);

#endif // SCHED_PROC
