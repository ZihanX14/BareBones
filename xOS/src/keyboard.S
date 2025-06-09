/* keyboard.S */
#include <xos.h>
.global keyboard_isr
.type keyboard_isr, @function
keyboard_isr:
    cli                 # Disable further interrupts
    pusha
    call keyboard_handler
    popa
    sti                 # Re-enable before returning
    iret
