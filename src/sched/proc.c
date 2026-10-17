#include "../mem/pmm.h"
#include "../mem/kmalloc.h"
#include "../util/alias.h"
#include "proc.h"
#include "test/test.h"
#include "../util/memory.h"

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

	proc.ctx.intf.gp = (struct gp_regs) {0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	proc.ctx.intf.hw.rsp = vmalloc(stack_size) + stack_size;
	proc.stbase = proc.ctx.intf.hw.rsp;
	proc.ctx.intf.hw.rflags = (size_t) 0x202;
	// Considering real programs, they will be loaded from storage, so this
	// is just a dummy implementation anyway, so
	// TODO! substitute this.
	proc.ctx.intf.hw.rip = vmalloc(5000);
	memcpy(proc.ctx.intf.hw.rip, ptr, 5000);
	

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

static inline void proc_switch_inline(struct int_frame *intf)
{
	procs[current_proc_id].ctx.intf = *intf;
	procs[current_proc_id].state = PROC_READY;
} void proc_switch(struct int_frame *intf) { return proc_switch_inline(intf); }


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
		procs[current_proc_id].ctx.intf = *intf;
		//print_hex((uint64_t)procs[current_proc_id].ctx.intf.rip);
		//print_hex((uint64_t)procs[current_proc_id].ctx.intf.rsp);
	} else defined = true;
	if (current_proc_id == 0) {
		print_line("fizz\n");
		current_proc_id = 1;
	} else {
		print_line("foo!\n");
		current_proc_id = 0;
	}
	return &procs[current_proc_id];
}
