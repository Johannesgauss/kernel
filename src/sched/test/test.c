#include "test.h"
#include "util/alias.h"
#include "drivers/gfx/print_text.h"
extern void retsys();
int foo()
{
	//print_line("I'm foo!\n");
	//while (1) {
	//asm volatile ("nop");
		//print_line("I'm foo!\n");
		//for (uint64_t i = 0; i < 0xFFFFF; i++) { asm volatile ("nop"); //asm volatile ("cli; hlt"); }
	//}

	//asm volatile ("sti");
	//while (1) { asm volatile ("cli; hlt"); }
	
	retsys();
}

int fizz()
{
	//print_line("I'm fizz!\n");
	while (1) {
		//print_line("I'm fizz!\n");
//		for (uint64_t i = 0; i < 0xFFFFF; i++) { asm volatile ("nop"); //asm volatile ("cli; hlt"); }
	}

	//asm volatile ("sti");
	//while (1) { asm volatile ("cli; hlt"); }
	
	retsys();
}
