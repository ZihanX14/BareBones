/* start.S
 * Bootstrap Assembly to
 * Declare constants for the multiboot header (global variables) 
 * multiboot header must be very early in the kernel binary 
 */
.set ALIGN,     1<<0                /* align loaded modules on page boundaries */
.set MEMINFO,   1<<1                /* provide memory map */
.set FLAGS,     ALIGN | MEMINFO     /* Multiboot 'flag' field */
.set MAGIC,     0x1BADB002          /* 'magic number' lets bootloader find the header */
.set CHECKSUM,  -(MAGIC + FLAGS)    /* */


.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	cli
	mov $stack_top, %esp

	call main

1:	hlt
	jmp 1b

.size _start, . - _start