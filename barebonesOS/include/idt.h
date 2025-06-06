#pragma once
#include <stdint.h>

/* IA_32 IDT entry table*/
struct IDTEntry {
    uint16_t base_low;  //offset 1
    uint16_t sel;       //selector
    uint8_t  always0;   //unused
    uint8_t  flags;     //gate type, dpl, p fields
    uint16_t base_high; //high offsets (16-32)
} __attribute__((packed));

struct IDTPointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_flush(uint32_t);
