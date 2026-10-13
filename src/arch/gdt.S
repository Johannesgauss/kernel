.global gdt_load
.type gdt_load, @function
gdt_load:
	lgdt (%rdi)
	push $0x08
	lea gdt_load_end(%rip), %rax
	push %rax
	lretq

gdt_load_end:
	mov $0x10, %rax
	mov %rax, %ds
	mov %rax, %ss
	mov %rax, %es
	mov %rax, %fs
	mov %rax, %gs

 	mov $0x28, %rax
	ltr %rax

	ret
