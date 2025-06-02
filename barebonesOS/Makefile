#
# make: build kernel and GDT, link to myos.bin, copy to isodir, build ISO
# make clean: remove build artifacts
# make run: boot in QEMU
#

# Cross compiler
CC = i686-elf-gcc
AS = i686-elf-as

# Compilation and Linking flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

# Sources
C_SOURCES = kernel.c gdt.c
ASM_SOURCES = start.s gdt_flush.s

# Object files
OBJS = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.s=.o)

# Targets and file paths
BIN = myos.bin
ISO = myos.iso
ISO_DIR = isodir
GDT = gdt.o gdt_flush.o
GRUB_CFG = $(ISO_DIR)/boot/grub/grub.cfg

# Default target to build everything
all: $(ISO)

# Compile C source files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Assemble assembly source files
%.o: %.s
	$(AS) $< -o $@

gdt_flush.o: gdt_flush.s
	$(CC) -c $< -o $@
gdt.o: gdt.c gdt.h
	$(CC) -c $< -o $@ $(CFLAGS)

# Link object files into kernel binary
$(BIN): $(BOOT) $(KERNEL) $(GDT)
	$(CC) $(LDFLAGS) -o $@ $^ -lgcc

# Copy kernel binary into ISO directory
$(ISO_DIR)/boot/$(BIN): $(BIN)
	cp $< $@

# Build bootable ISO image using GRUB
$(ISO): $(ISO_DIR)/boot/$(BIN) $(GRUB_CFG)
	grub-mkrescue -o $@ $(ISO_DIR)

# Clean up build artifacts
clean:
	rm -f $(BIN) $(OBJS) $(ISO) $(ISO_DIR)/boot/$(BIN)

# Run in QEMU
run: all
	qemu-system-i386 -cdrom $(ISO)
