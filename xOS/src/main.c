/* main.c */
#include <xos.h>

void main(void) 
{
	gdt_init();
	idt_init();

	/* Initialize terminal interface */
	terminal_initialize();
	//terminal_writestring("Starts Clock\n");
	/* Newline support is left as an exercise. */
	// terminal_writestring("hello world\n");
	
	/* initialize memory*/
	mem_init();
	pic_remap();
	
	idt_set_gate(32, (uint32)clock_isr, 0x08, 0x8E); // prevent triple fault
	//clock_init();
	keyboard_init();
	asm volatile ("sti"); // enable interrupts
	shell_init();
}