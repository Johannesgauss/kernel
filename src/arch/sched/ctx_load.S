#define KERNEL_CODE 0x08
#define KERNEL_DATA 0x10
#define USER_CODE 0x1b
#define USER_DATA 0x23
.global sched_interruption
.type sched_interruption, @function
.extern tss
.global ctx_load
.type ctx_load, @function
ctx_load:
	mov %rsp, tss+4(%rip) 

	push $USER_DATA
	push %rsi
	pushfq
	push $USER_CODE
	push %rdi

	iretq

.extern interruption_handler
.type interruption_handler, @function
sched_interruption:
	cld
	// TODO: for the majority of functions, this doesn't make sense
	// Furthermore, use asm macros in the future!
	movq %rsp, %rdi
	call interruption_handler

	iretq
