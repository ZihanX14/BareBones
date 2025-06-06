/* uti.S */


/* enable - enable interrupt */
enable:
    cli     /* disable interrupt for infinite loop */

/* disable - disable interrupt */
disable:
    sti     /* Sets the interrupt flag, letting the cpu serve interrupts. */

halt:
    hlt