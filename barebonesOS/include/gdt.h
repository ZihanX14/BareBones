#pragma once
#include <stdint.h>

struct GDT {
    uint32_t base;
    uint32_t limit;
    uint8_t access_byte;
    uint8_t flags;
};

void gdt_install(void);
void gdt_flush(uint32_t);
