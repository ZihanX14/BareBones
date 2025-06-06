/* clock_handler.c */
#include <os.h>
#include <stdint.h>


static int ticks = 0;
static int second = 0;
int timer_enable = 1;

void toggle_output(){
    timer_enable = !timer_enable;
}

void clock_handler() {
    if (timer_enable != 1){
        outb(0x20, 0x20);
        return;
    }
    ticks++;
    /* print one line for each second: PIT 100Hz*/
    if (ticks % 100 == 0) {
        second++;
        terminal_writestring("Second");
        //terminal_putchar('0' + second);
        terminal_putchar('0' + (second % 10));
        terminal_putchar('\n');
    }
    // terminal_writestring("Tick");
    // terminal_putchar('0' + (ticks % 100));
    // terminal_putchar('\n');

    // Send End of Interrupt (EOI) to PIC master
    outb(0x20, 0x20);
}
