#
# make: build kernel.o myos.bin, copy to isodir/boot/myos.bin, build myos.iso
# make clean: remove kernel.o myos.bin myos.iso
# make run: run qemu-system-i386 -cdrom myos.iso
#

# Cross compiler
CC = i686-elf-gcc

# Compilation and Linking flags
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

# Targets and file paths
KERNEL = kernel.o
BOOT = boot.o
BIN = myos.bin
ISO = myos.iso
ISO_DIR = isodir
GRUB_CFG = $(ISO_DIR)/boot/grub/grub.cfg

# Default target to build everything for myos.iso
all: $(ISO)

# Compile kernel: i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
$(KERNEL): kernel.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Link object files into kernel binary: i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
$(BIN): $(BOOT) $(KERNEL)
	$(CC) $(LDFLAGS) -o $@ $^ -lgcc

#Copy binary into ISO folder: cp myos.bin isodir/boot/myos.bin
$(ISO_DIR)/boot/$(BIN): $(BIN)
	cp $< $@

# Build bootable iso: grub-mkrescue -o myos.iso isodir
$(ISO): $(ISO_DIR)/boot/$(BIN) $(GRUB_CFG)
	grub-mkrescue -o $@ $(ISO_DIR)

# Cleanup
clean:
	rm -f $(BIN) $(KERNEL) $(ISO) $(ISO_DIR)/boot/$(BIN)

# Run (Optional)
run: all
	qemu-system-i386 -cdrom $(ISO)