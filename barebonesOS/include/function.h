/*function.h*/
/*clock_handler.c*/
extern void toggle_output(void);
extern void clock_handler(void); 

/*clock.s*/
extern void clock_isr(void);

/*clockinit.c*/
extern void clock_init(void);

/*gdt_flush.S*/
extern void gdt_flush(void);
extern void flush(void);

/*gdt.c*/
extern void encode_gdt_entry(uint8 *target, struct GDT source);
extern void gdt_init(void);

/*idt_flush.s*/
extern void idt_flush(void);

/*idt.c*/
extern void idt_set_gate(uint8, uint32, uint16, uint8);
extern void idt_init(void);

/*interrupt.c*/
extern void stop_outoput(void);

/*kernel.c*/
extern inline uint8 vga_entry_color(enum vga_color fg, enum vga_color bg);
