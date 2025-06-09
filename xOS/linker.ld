/* link boot.o and kernel.o object files into final kernel program usable by bootloader */
/* booloader look at linker.ld image and start execution at the entry point */
/* link using i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc*/
ENTRY(_start)

SECTIONS{
    . = 2M;
    .text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
    .rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
    .data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
    .bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

	_end = .;
}