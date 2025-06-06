#include <os.h>

void pic_remap() {
    // Initialization Control Words
    outb(0x20, 0x11); // Start init of master PIC
    outb(0xA0, 0x11); // Start init of slave PIC

    outb(0x21, 0x20); // Master PIC vector offset (IRQ0-7 => 32–39)
    outb(0xA1, 0x28); // Slave PIC vector offset (IRQ8-15 => 40–47)

    outb(0x21, 0x04); // Tell Master PIC there’s a slave at IRQ2
    outb(0xA1, 0x02); // Tell Slave PIC its cascade identity

    outb(0x21, 0x01); // 8086 mode
    outb(0xA1, 0x01); // 8086 mode

    outb(0x21, 0x0);  // Unmask all IRQs on master
    outb(0xA1, 0x0);  // Unmask all IRQs on slave
}
