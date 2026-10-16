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
	procs[0] = proc_create(&foo, 5000);
	procs[1] = proc_create(&fizz, 5000);
}

static inline struct proc proc_inst_inline(state_t state, virt_t ptr, size_t stack_size)
{
	struct proc proc;

	proc.id = id_count;
	id_count++;

	proc.state = state;

	proc.ctx.gp = (struct gp_regs) {0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	proc.ctx.hw.rsp = vmalloc(stack_size) + stack_size;
	proc.stbase = proc.ctx.hw.rsp;
	proc.ctx.hw.rip = ptr;
	proc.ctx.hw.rflags = (size_t) 0x202;

	return proc;
} struct proc proc_inst(state_t state, virt_t ptr, size_t stack_size) { return proc_inst_inline(state, ptr, stack_size); }

static inline void proc_kill_inline(ushort id)
{
	procs[id].state = PROC_DEAD;
	vfree(procs[id].stbase);
} void proc_kill(ushort id) { return proc_kill_inline(id); }

static inline void proc_exit_inline(int retvalue)
{
	procs[current_proc_id].retvalue = retvalue;
	proc_kill_inline(current_proc_id);
} void proc_exit(int retvalue) { return proc_exit_inline(retvalue); }

static inline void proc_suspend_inline(ushort id)
{
	procs[id].state = PROC_READY;
} void proc_suspend(ushort id) { return proc_suspend_inline(id); }

static inline void proc_switch_inline(struct int_frame *ctx)
{
	procs[current_proc_id].ctx = *ctx;
	procs[current_proc_id].state = PROC_READY;
} void proc_switch(struct int_frame *ctx) { return proc_switch_inline(ctx); }


struct proc proc_create(virt_t ptr, size_t stack_size)
{
	struct proc proc = proc_inst_inline(PROC_READY, ptr, stack_size);

	return proc;
}

struct proc *proc_sched(struct int_frame *intf)
{
	// TODO: I don't think this is the better solution!
	static bool defined = false;
	if (defined) {
		procs[current_proc_id].ctx = *intf;
		//print_hex((uint64_t)procs[current_proc_id].ctx.rip);
		//print_hex((uint64_t)procs[current_proc_id].ctx.rsp);
	} else defined = true;
	if (current_proc_id == 0)
		current_proc_id = 1;
	else 
		current_proc_id = 0;
	return &procs[current_proc_id];
}
