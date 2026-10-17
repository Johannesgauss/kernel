extern void sys_exit(int retvalue);
extern void print_line(char *line);

void syscall_handler(int code, int param)
{
	if (code == 0) {
		sys_exit(param);
	}
}
