#include <idt.h>

#define IDT_ENTRIES 256

static struct IDTEntry idt[IDT_ENTRIES];
static struct IDTPointer idtp;

extern void idt_flush(uint32_t);

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init() {
    idtp.limit = sizeof(struct IDTEntry) * IDT_ENTRIES - 1;
    idtp.base = (uint32_t)&idt;

    // Clear IDT entries
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    // You can set handlers like this later
    // idt_set_gate(32, (uint32_t)isr32, 0x08, 0x8E);

    idt_flush((uint32_t)&idtp);
}
