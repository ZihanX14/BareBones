# BareBones
OS Dev Bare Bones kernel project  
https://wiki.osdev.org/Bare_Bones  
    The GNU Linker from Binutils to link your object files into the final kernel.  
    The GNU Assembler from Binutils (or optionally NASM) to assemble instructions into object files containing machine code.  
    The GNU Compiler Collection to compile your high level code into assembly.  
    The C programming language (or optionally C++) to write the high level parts of your kernel.  
    The GRUB bootloader to bootload your kernel using the Multiboot boot protocol that loads us into 32-bit protected mode with paging disabled.  
    The ELF as the executable format that gives us control of where and how the kernel is loaded.  

GCC Cross-compiler:  
a cross-compiler is a compiler that runs on platform A (the host), but generates executables for platform B (the target).

gcc-14.3.0
gdb-16.3
binutils-2.44

export PREFIX="$HOME/opt/cross"  
export TARGET=i686-elf  
export PATH="$PREFIX/bin:$PATH"

Multiboot Standard

assemble boot.s with i686-elf-as boot.s -o boot.o