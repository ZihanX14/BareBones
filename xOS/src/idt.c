#include <xos.h>

#define IDT_ENTRIES 256

/* IA_32 IDT entry table*/
struct IDTEntry {
    uint16 base_low;  //offset 1
    uint16 sel;       //selector
    uint8  always0;   //unused
    uint8  flags;     //gate type, dpl, p fields
    uint16 base_high; //high offsets (16-32)
} __attribute__((packed));

struct IDTPointer {
    uint16 limit;
    uint32 base;
} __attribute__((packed));

static struct IDTEntry idt[IDT_ENTRIES];
static struct IDTPointer idtp;

void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags){
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init(){
    idtp.limit = sizeof(struct IDTEntry) * IDT_ENTRIES - 1;
    idtp.base = (uint32)&idt;

    // Clear IDT entries
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    // You can set handlers like this later
    // idt_set_gate(32, (uint32_t)isr32, 0x08, 0x8E);

    idt_flush((uint32)&idtp);
}
