#
# Make: Build kernel, link to myos.bin, copy to isodir, and create ISO
# Clean: Remove all build artifacts
# Run: Boot ISO in QEMU
#

# Directories
SRC_DIR = src
INC_DIR := include
BUILD_DIR := build
ISO_DIR := isodir
BOOT_DIR := $(ISO_DIR)/boot

# Tools
CC := i686-elf-gcc
AS := i686-elf-as
LD := i686-elf-gcc

# Flags
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INC_DIR)
CFLAGS += -fno-toplevel-reorder -fno-unit-at-a-time
LDFLAGS := -T linker.ld -nostdlib

# Sources
C_SOURCES := main.c terminal.c gdt.c idt.c pic.c clockinit.c clock_handler.c keyboardinit.c keyboard_handler.c meminit.c shell.c strcmp.c read.c
ASM_SOURCES := start.S gdt_flush.S idt_flush.S clock.S keyboard.S
# To enable clock interrupt later:
# ASM_SOURCES += clock.s

# Object file list
C_OBJS := $(addprefix $(BUILD_DIR)/, $(C_SOURCES:.c=.o))
ASM_OBJS := $(addprefix $(BUILD_DIR)/, $(ASM_SOURCES:.S=.o))
OBJS := $(C_OBJS) $(ASM_OBJS)

# Output files
BIN := myos.bin
ISO := myos.iso
GRUB_CFG := $(ISO_DIR)/boot/grub/grub.cfg

# Default target
all: $(ISO)

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Assemble .S files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	mkdir -p $(BUILD_DIR)
	$(AS) $< -o $@

# Link kernel binary
$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# Copy to ISO dir
$(BOOT_DIR)/$(BIN): $(BIN)
	mkdir -p $(BOOT_DIR)
	cp $< $@

# Build bootable ISO
$(ISO): $(BOOT_DIR)/$(BIN) $(GRUB_CFG)
	grub-mkrescue -o $@ $(ISO_DIR)

# Clean up
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN) $(ISO) $(BOOT_DIR)/$(BIN)

# Run in QEMU
run: all
	qemu-system-i386 -cdrom $(ISO)
