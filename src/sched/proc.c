#include "../mem/pmm.h"
#include "../arch/sched/proc_ctx.h"
#include "../util/alias.h"

#define PROCS_MAX 255


extern void retsys();
int foo()
{
	print_line("I'm foo!\n");
	for (uint64_t i = 0; i < 0xFFFFFFF; i++) {
		asm volatile ("nop");
		//asm volatile ("cli; hlt");
	}

	//asm volatile ("sti");
	//while (1) { asm volatile ("cli; hlt"); }
	
	retsys();
}

int fizz()
{
	print_line("I'm fizz!\n");
	for (uint64_t i = 0; i < 0xFFFFFFF; i++) {
		asm volatile ("nop");
		//asm volatile ("cli; hlt");
	}

	//asm volatile ("sti");
	//while (1) { asm volatile ("cli; hlt"); }
	
	retsys();
}





typedef enum {
	PROC_DEAD = 0,
	PROC_EXEC = 1,
	PROC_BLOCK = 2,
	PROC_READY = 3
} state_t;

struct proc {
	utiny id;
	state_t state;
	struct proc_arch_ctx ctx;
};


static ushort id_count = 0;
static ushort current_proc_id = 0;

static uint64_t stack[5000];
static uint64_t stack2[5000];

struct proc proc_create(state_t state, struct proc_arch_ctx ctx);
// TODO: a better implementation
struct proc procs[2] = {
	{0, PROC_READY, (struct proc_arch_ctx){0, &foo, stack+500}},
	{1, PROC_READY, (struct proc_arch_ctx){0, &fizz, stack2+500}},
}; // because id is ushort

struct proc proc_create(state_t state, struct proc_arch_ctx ctx)
{
	struct proc proc;

	proc.id = id_count;
	id_count++;

	proc.state = state;
	proc.ctx = ctx;

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

void proc_exit(int retvalue)
{
	if (!retvalue)
		print_line("SUCESS! ->");
	procs[current_proc_id].state = PROC_DEAD;
	if (current_proc_id == 0)
		current_proc_id = 1;
	else 
		current_proc_id = 0;
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

struct proc proc_sched()
{
	return procs[current_proc_id];
}
