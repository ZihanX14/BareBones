.global clock_isr
clock_isr:
    pusha
    call clock_handler
    popa
    iret