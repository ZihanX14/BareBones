/* keyboard.s */
.global keyboard_isr
keyboard_isr:
    pusha
    call keyboard_handler
    popa
    iret