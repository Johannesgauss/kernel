#include "../mem/pmm.h"
#include "../mem/kmalloc.h"
#include "../util/alias.h"
#include "proc.h"
#include "test/test.h"
#include "../util/memory.h"

static struct proc proc_inst_inline(state_t state, virt_t ptr, umax stack_size);
static struct proc proc_create_inline(virt_t ptr, umax code_size, umax stack_size);
static void proc_kill_inline(ushort id);
static void proc_exit_inline(int retvalue);
static struct proc *proc_sched_inline(struct int_frame *hf);
static void proc_suspend_inline(ushort id);
static void proc_switch_inline(struct int_frame *intf);

struct proc proc_inst(state_t state, virt_t ptr, umax stack_size) { return proc_inst_inline(state, ptr, stack_size); }
void proc_kill(ushort id) { return proc_kill_inline(id); }
void proc_exit(int retvalue) { return proc_exit_inline(retvalue); }
void proc_suspend(ushort id) { return proc_suspend_inline(id); }
void proc_switch(struct int_frame *intf) { return proc_switch_inline(intf); }

// TODO: a better implementation
#define PROCS_HASH_TABLE_SIZE 255
static struct proc *proc_hash_table[PROCS_HASH_TABLE_SIZE];

static struct proc *htid_search(max id);
static void htid_insert(struct proc *proc);

static ushort id_count = 0;
static ushort current_proc_id = 0;

static struct proc *htid_search_inline(max id)
{
	struct proc *current = proc_hash_table[id];
	while (current->id != id) {
		current = current->next;	
	}

	return current;
}
static struct proc *htid_search(max id) { return htid_search_inline(id); }

static umax htid_gen(max id)
{
	return 5;		
}

static void htid_insert(struct proc *proc)
{
	umax id = htid_gen(proc->id);
	struct proc *bottom = proc_hash_table[id];
	if (bottom) {
		bottom->prev = proc;
		proc->next = bottom;
	} else {
		proc_hash_table[id] = proc;
	}

}

static void htid_rm(max id)
{
	struct proc *current = htid_search_inline(id);	
	if (current->prev && current->next) {
		current->prev->next = current->next;
	} else if (current->prev) {
		current->prev->next = NULL;
	} else if (current->next) {
		current->next->prev = NULL;
		proc_hash_table[id] = NULL;
	}

	kfree(current);
}

void proc_tmp_setup()
{
	procs[0] = proc_create(&foo, 5000, 5000);
	procs[1] = proc_create(&fizz, 5000, 5000);
}

static inline struct proc proc_inst_inline(state_t state, virt_t ptr, umax stack_size)
{
	struct proc proc;

	proc.id = id_count;
	id_count++;

	proc.state = state;

	proc.ctx.intf.gp = (struct gp_regs) {0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	return proc;
}

static inline void proc_kill_inline(ushort id)
{
	procs[id].state = PROC_DEAD;
	vfree(procs[id].stbase);
}

static inline void proc_exit_inline(int retvalue)
{
	procs[current_proc_id].retvalue = retvalue;
	proc_kill_inline(current_proc_id);
}

static inline void proc_suspend_inline(ushort id)
{
	procs[id].state = PROC_READY;
}

static inline void proc_switch_inline(struct int_frame *intf)
{
	procs[current_proc_id].ctx.intf = *intf;
	procs[current_proc_id].state = PROC_READY;
}

struct proc proc_create(virt_t ptr, umax code_size, umax stack_size)
{
	struct proc proc = proc_inst_inline(PROC_READY, ptr, stack_size);

	arch_proc_init(&proc.ctx);

	proc.ctx.intf.hw.rsp = usr_vmalloc(stack_size) + stack_size;
	proc.stbase = proc.ctx.intf.hw.rsp;
	proc.ctx.intf.hw.rflags = (1 << 9) | 0b10;
	// Considering real programs, they will be loaded from storage, so this
	// is just a dummy implementation anyway, so
	// TODO! substitute this.

	proc.ctx.intf.hw.rip = usr_vmalloc(code_size);
	memcpy(proc.ctx.intf.hw.rip, ptr, code_size);

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
