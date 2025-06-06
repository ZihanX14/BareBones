/*function.h*/
#include <stdint.h>
void terminal_writestring(const char*);
void terminal_putchar(char c);
void clock_handler(void);
void clock_init(void);
void toggle_output(void);
void keyboard_init(void);
uint8_t keyboard_to_ascii(uint8_t);