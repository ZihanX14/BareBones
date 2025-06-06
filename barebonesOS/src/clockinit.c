#include <os.h>
#include <io.h>

extern void clock_isr(void);

/**
 *  Make space for the interrupt descriptor table
    Tell the CPU where that space is (see GDT Tutorial: lidt works the very same way as lgdt)
    Tell the PIC that you no longer want to use the BIOS defaults (see Programming the PIC chips)
    Write a couple of ISR handlers (see Interrupt Service Routines) for both IRQs and exceptions
    Put the addresses of the ISR handlers in the appropriate descriptors (in Interrupt Descriptor Table)
    Enable all supported interrupts in the IRQ mask (of the PIC)
 */

void clock_init() {
    pic_remap();

    // Register clock interrupt handler (IRQ0 = vector 32)
    idt_set_gate(32, (uint32_t)clock_isr, 0x08, 0x8E);

    // Initialize PIT to 100Hz
    uint32_t divisor = 1193180 / 100; // ~100Hz
    outb(0x43, 0x36);                 // Command port: Channel 0, LSB/MSB, Mode 3 (periodic)
    outb(0x40, divisor & 0xFF);       // Channel 0 data port: low byte
    outb(0x40, (divisor >> 8) & 0xFF); // high byte
}