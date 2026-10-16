#define ctx_off 0
.global int_handler
.type int_handler, @function
.extern tss
#define KERNEL_CODE 0x08
#define KERNEL_DATA 0x10
#define USER_CODE 0x1b
#define USER_DATA 0x23
#include "drivers/clk/pit_defs.h"
int_handler:
	pushq %r15
	pushq %r14
	pushq %r13
	pushq %r12
	pushq %r11
	pushq %r10
	pushq %r9
	pushq %r8
	pushq %rbp
	pushq %rdi
	pushq %rsi
	pushq %rdx
	pushq %rcx
	pushq %rbx
	pushq %rax

	mov %rsp, %rdi
	call proc_sched
	mov %rax, %rbx

	mov $PIC1_COMMAND, %rdi
	mov $PIC_EOI, %rsi
	call outb
	// until here, it's right

	popq %rax
	movq %rbx, %rax
	popq %rbx
	popq %rcx
	popq %rdx
	popq %rsi
	popq %rdi
	popq %rbp
	popq %r8
	popq %r9
	popq %r10
	popq %r11
	popq %r12
	popq %r13
	popq %r14
	popq %r15
	// inside %rax lies the new process!
	
	// to get rip
	mov ctx_off+0x78(%rax), %rdi
	// to get rax
	mov ctx_off+0x90(%rax), %rsi

	add $0x28, %rsp
	mov %rsp, tss+4(%rip) 

	push $KERNEL_DATA
	push %rsi // stack
	//pushfq
	push $0x202 // TODO a better way!
	push $KERNEL_CODE
	push %rdi

	mov ctx_off+0x70(%rax), %r15
	mov ctx_off+0x68(%rax), %r14
	mov ctx_off+0x60(%rax), %r13
	mov ctx_off+0x58(%rax), %r12
	mov ctx_off+0x50(%rax), %r11
	mov ctx_off+0x48(%rax), %r10
	mov ctx_off+0x40(%rax), %r9
	mov ctx_off+0x38(%rax), %r8
	mov ctx_off+0x30(%rax), %rbp
	mov ctx_off+0x28(%rax), %rdi
	mov ctx_off+0x20(%rax), %rsi
	mov ctx_off+0x18(%rax), %rdx
	mov ctx_off+0x10(%rax), %rcx
	mov ctx_off+8(%rax), %rbx
	push ctx_off+0(%rax)
	pop %rax

	iretq
