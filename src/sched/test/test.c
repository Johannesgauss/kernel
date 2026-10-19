#include "test.h"
#include "util/alias.h"
#include "drivers/gfx/print_text.h"
extern void retsys();
int foo()
{
	//print_line("I'm foo!\n");
	for (long i = 0; i < 0xFFFFFFF; i++) { 
		asm volatile ("nop");
	}
	
	retsys();
}

int fizz()
{
	for (long i = 0; i < 0xFFFFFFF; i++) { 
		asm volatile ("nop");
	}
	
	retsys();
}
