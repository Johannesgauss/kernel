.global sched_interruption
.type sched_interruption, @function
.extern interruption_handler
.type interruption_handler, @function
sched_interruption:
	// TODO: verify it under debugger later!
	// The ideia here is removing the stack suffed hardware did to a random register
	// in this case, rax
	pop %rax
	pop %rax
	pop %rax
	pop %rax
	pop %rax

	cld
	// TODO: for the majority of functions, this doesn't make sense
	// Furthermore, use asm macros in the future!
	//mov %rsp, %rdi
	call interruption_handler
.extern tss
.global ctx_load
.type ctx_load, @function
#define KERNEL_CODE 0x08
#define KERNEL_DATA 0x10
#define USER_CODE 0x1b
#define USER_DATA 0x23
ctx_load:
	mov %rsp, %rax

	mov %rsp, tss+4(%rip) 

	push $KERNEL_DATA
	push %rsi // stack
	pushfq
	//push $0x202 // TODO a better way!
	push $KERNEL_CODE
	push %rdi

	iretq
