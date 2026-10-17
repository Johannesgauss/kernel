#include "idt.h"
struct arch_proc {
	uint64_t cr3;
	struct int_frame intf;
};
