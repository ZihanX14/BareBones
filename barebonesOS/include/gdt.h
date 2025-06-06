#pragma once
#include <stdint.h>

struct GDT {
    uint32_t base;
    uint32_t limit;
    uint8_t access_byte;
    uint8_t flags;
}__attribute__((packed));

void gdt_init(void);
void encode_gdt_entry(uint8_t *target, struct GDT source);
void gdt_flush(uint32_t);
