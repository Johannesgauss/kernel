#define ctx_off 0
.global int_handler
.type int_handler, @function
.extern tss
#include "arch/gdt_macros.h"
#include "drivers/clk/clk_macros.h"
// was_todo: comment it better!
// Update: Done!
int_handler:
	push %r15
	push %r14
	push %r13
	push %r12
	push %r11
	push %r10
	push %r9
	push %r8
	push %rbp
	push %rdi
	push %rsi
	push %rdx
	push %rcx
	push %rbx
	push %rax

	mov %rsp, %rdi
	call proc_sched
	mov %rax, %rbx
	// inside %rbx lies the new process!

	mov $PIC1_COMMAND, %rdi
	mov $PIC_EOI, %rsi
	call outb

	add $0xA0, %rsp // d15*8 + 0x28 = 0xA0
	// 0x28 because of hw_frame stuff pushed by machine
	
	// to get rip
	mov ctx_off+0x78(%rbx), %rdi
	// to get rflags
	mov ctx_off+0x88(%rbx), %rsi
	// to get rsp
	mov ctx_off+0x90(%rbx), %rdx

	mov %rsp, tss+4(%rip) 

	push $GDT_OFFSET_USER_DATA
	push %rdx // stack
	//pushfq
	push %rsi
	//push $0x202 // TODO a better way!
	push $GDT_OFFSET_USER_CODE
	push %rdi

	mov ctx_off+0x70(%rbx), %r15
	mov ctx_off+0x68(%rbx), %r14
	mov ctx_off+0x60(%rbx), %r13
	mov ctx_off+0x58(%rbx), %r12
	mov ctx_off+0x50(%rbx), %r11
	mov ctx_off+0x48(%rbx), %r10
	mov ctx_off+0x40(%rbx), %r9
	mov ctx_off+0x38(%rbx), %r8
	mov ctx_off+0x30(%rbx), %rbp
	mov ctx_off+0x28(%rbx), %rdi
	mov ctx_off+0x20(%rbx), %rsi
	mov ctx_off+0x18(%rbx), %rdx
	mov ctx_off+0x10(%rbx), %rcx

	mov ctx_off+0(%rbx), %rax
	mov ctx_off+8(%rbx), %rbx

	iretq
