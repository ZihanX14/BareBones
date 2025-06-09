/* read.c - read_line*/
#include <xos.h>

void read_line(char *dest, int maxlen) {
    asm volatile("cli");  // Disable interrupts
    input_ready = 0;
    input_len = 0;
    asm volatile("sti");  // Enable interrupts BEFORE loop

    while (!input_ready) {
        asm volatile("hlt");  // Sleep until next interrupt
    }

    int len = (input_len < maxlen - 1) ? input_len : maxlen - 1;
    for (int i = 0; i < len; i++) {
        dest[i] = input_buf[i];
    }
    dest[len] = '\0';
    input_len = 0;
}





