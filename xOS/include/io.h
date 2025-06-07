/* Write a byte to an I/O port */
static inline void outb(uint16 port, uint8 val) {
    asm volatile ( "outb %0, %1" :: "a"(val), "Nd"(port) );
}

/* Read a byte from an I/O port */
static inline uint8 inb(uint16 port) {
    uint8 ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}