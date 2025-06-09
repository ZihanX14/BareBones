/*function.h - include all the functions*/

/*terminal.c*/
extern void terminal_initialize(void);
extern void terminal_setcolor(uint8 color);
extern void terminal_newline(void);
extern void terminal_scroll(void);
extern void terminal_putentryat(char c, uint8 color, size x, size y);
extern void terminal_putchar(char c);
extern void terminal_write(const char* data, size size);
extern void terminal_writestring(const char* data);
extern void terminal_set_cursor (int x, int y);
extern void itoa(uint32 value, char *str);

/*gdt.c*/
struct GDT;
extern void gdt_init(void);
extern void encode_gdt_entry(uint8 *target, struct GDT *source);
extern void gdt_flush(uint32);

/*gdt_flush.S*/
extern void gdt_flush(uint32);
extern void flush(void);

/*idt.c*/
extern void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags);
extern void idt_init(void);

/*idt_flush.S*/
extern void idt_flush(uint32);

/*pic.c*/
extern void pic_remap(void);

/*clock.S*/
extern void clock_isr(void);

/*clockinit.c*/
extern void clock_init(void);

/*clock_handler.c*/
extern void toggle_output(void);
extern void clock_handler(void);

/*keyboard.S*/
extern void keyboard_isr(void);

/*keyboardinit.c*/
extern uint8 keyboard_to_ascii(uint8 key);
extern void keyboard_init(void);

/*keyboard_handler.c*/
extern __attribute__((used)) void keyboard_handler(void);

/*meminit.c*/
extern void mem_init(void);

/*shell.c*/
extern process shell_init(void);

/*read.c*/
extern void read_line(char *dest, int maxlen);

/*LIBC*/
/*strcmp.c*/
extern int strcmp(const char* a, const char* b);
