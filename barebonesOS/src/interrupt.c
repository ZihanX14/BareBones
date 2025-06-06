/* interrupt.c */
#include <os.h>

int timer_enable = 1;

void stop_outoput(){
    timer_enable = 0;
}