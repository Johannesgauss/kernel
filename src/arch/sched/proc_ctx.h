#ifndef ARCH_SCHED_H
#define ARCH_SCHED_H
#include "../../util/alias.h"

struct proc_arch_ctx {
	void *cr3;
	void *rip;
	void *rsp;
};

#endif // ARCH_SCHED_H
