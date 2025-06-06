/* keyboard_handler.c - handle keyboard commands PS/2 Keyboard: https://wiki.osdev.org/PS/2_Keyboard*/

/*TODO: Command Queue, state machine, IRQ(interrupt request) handler*/

/** Command Queue:
 * add command to queue, 
 * if queue empty -> send command
 * else -> append command to queue
 * 
 * if receive ACK(0xFA) from keyboard, discard command at the head and send next command
 * if receive Resend(0xFE), resend command at the head of queue
 * 
 *  Make space for the interrupt descriptor table
    Tell the CPU where that space is (see GDT Tutorial: lidt works the very same way as lgdt)
    Tell the PIC that you no longer want to use the BIOS defaults (see Programming the PIC chips)
    Write a couple of ISR handlers (see Interrupt Service Routines) for both IRQs and exceptions
    Put the addresses of the ISR handlers in the appropriate descriptors (in Interrupt Descriptor Table)
    Enable all supported interrupts in the IRQ mask (of the PIC)
 * 
*/

#include <os.h>
#include <stdint.h>

extern void toggle_output();

/* TODO: create a buffer to store the input from keyboard till the user press Enter */
void keyboard_handler() {
   uint8_t scancode = inb(0x60);
   char ch = keyboard_to_ascii(scancode);
   if (ch) {
      terminal_writestring("Keyboard triggered: ");
      terminal_putchar(ch);
      terminal_putchar('\n');
      if (ch == '1'){
         terminal_writestring("Hello World\n");
      }
      toggle_output(); // disable timer display
   }
   outb(0x20, 0x20); // EOI
}
