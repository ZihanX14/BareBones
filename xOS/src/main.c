#include <xos.h>

void main(void) 
{
	gdt_init();
	idt_init();

	/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("Starts Clock\n");

	clock_init();
	keyboard_init();
	asm volatile ("sti"); // enable interrupts

	/* Newline support is left as an exercise. */
	//terminal_writestring("H\ne\nl\nl\no\n!\nk\ne\nr\nn\ne\nl\n \nW\no\nr\nl\nd\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!!\n");
}