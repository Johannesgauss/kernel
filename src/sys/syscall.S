.global sys_exit
.type sys_exit, @function
.global proc_exit
.type proc_exit, @function
.extern tss
sys_exit:
	mov tss+4, %rsp

	call proc_exit
	// TODO: This smells a bad solution
	sti
	int $32  // if the interruption happen before it?

.global retsys 
.type retsys, @function
retsys:
	mov $0, %rdi
	mov $0, %rsi
	int $0x80
