#define KERNEL_CODE 0x08
#define KERNEL_DATA 0x10
#define USER_CODE 0x18
#define USER_DATA 0x20
.global ctx_load
.type ctx_load, @function
.exter tss
ctx_load:
	mov %rsp, tss+4(%rip)

	mov $USER_DATA, %rax
	mov %rax, %ds
	mov %rax, %es
	mov %rax, %fs
	mov %rax, %gs

	push $USER_CODE
	push %rdi

	lretq
