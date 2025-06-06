/* kernel.c */
/**
 * uses VGA text mode buffer at 0xB8000 as output device
 * sets up a driver that remembers location of next character in the buffer
 * provides a primitive for addring a new character
 * no support for line breaks
 * no support for scrolling when screen is filled up
 * compile with i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <os.h>

/* macro to check if compiler thinks the target is the wrong os*/
#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif

/* Hardware text mode color constants for video graphic array*/
enum vga_color {
    VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
    return fg | bg << 4; //shift bg into high nibble (bit 4-7) and combine into 1 byte
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color){
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str){
    size_t len = 0;
    while (str[len]){
        len++;
    }
    return len;
}

/* standard VGA hardware text mode, the screen resolution is 80col x 25row*/
#define VGA_WIDTH   80
#define VGA_HEIGHT  25

/* write to a 2D buffer mapped at memory address 0xB8000*/
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
// uint8_t terminal_color_even;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	// terminal_color_even = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_WHITE);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			// if (x%2==0){
			// 	terminal_buffer[index] = vga_entry(' ', terminal_color_even);
			// }
			// else {
				terminal_buffer[index] = vga_entry(' ', terminal_color);
			// }
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

/* terminal_newline - move current input position to next line*/
void terminal_newline(){
	terminal_row += 1;
	terminal_column = 0;
}

/* when cursor reaches the bottom of the screen, move up by one row and clear last row*/
void terminal_scroll(){
	/* Move row up one */
	for (size_t y = 1; y < VGA_HEIGHT; y++){
		for (size_t x = 0; x < VGA_WIDTH; x++){
			terminal_buffer[(y - 1) * VGA_WIDTH + x] = terminal_buffer[y * VGA_WIDTH + x];
		}
	}
	/* clear last row */
	for (size_t x = 0; x < VGA_WIDTH; x++){
		terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
	}

	terminal_row = VGA_HEIGHT - 1;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	if (c == '\n'){
		terminal_newline();
	}
	else{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			terminal_row += 1;
		}
	}

	if (terminal_row == VGA_HEIGHT)
		//terminal_row = 0;
		terminal_scroll();

}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++){
		terminal_putchar(data[i]);
	}
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void kernel_main(void) 
{
	gdt_init();
	idt_init();

	/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("Starts Clock\n");

	clock_init();
	keyboard_init();
	asm volatile ("sti"); // enable interrupts

	/* Newline support is left as an exercise. */
	//terminal_writestring("H\ne\nl\nl\no\n!\nk\ne\nr\nn\ne\nl\n \nW\no\nr\nl\nd\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!!\n");
}