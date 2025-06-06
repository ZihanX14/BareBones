/* gdt.c - encode_gdt_entry, gdt_init*/

#include <stdint.h>
#include <gdt.h>

static uint8_t gdt[5 * 8]; // 5 entries, 8 bytes each

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct gdt_ptr gp;

void encode_gdt_entry(uint8_t *target, struct GDT source)
{
    // Check the limit to make sure that it can be encoded
    if (source.limit > 0xFFFFF) {
        //kerror("GDT cannot encode limits larger than 0xFFFFF");
        while(1);
    }
    
    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;
    
    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
    
    // Encode the access byte
    target[5] = source.access_byte;
    
    // Encode the flags
    target[6] |= (source.flags << 4);
}

void gdt_init(){
    struct GDT source[5] = {
        {0, 0, 0x00, 0x0},       // Null descriptor
        {0, 0xFFFFF, 0x9A, 0xC}, // Kernel code
        {0, 0xFFFFF, 0x92, 0xC}, // Kernel data
        {0, 0xFFFFF, 0xFA, 0xC}, // User code
        {0, 0xFFFFF, 0xF2, 0xC}  // User data
    };
        for (int i = 0; i < 5; i++) {
        encode_gdt_entry(&gdt[i * 8], source[i]);
    }

    gp.limit = sizeof(gdt) - 1;
    gp.base = (uint32_t)&gdt;

    gdt_flush((uint32_t)&gp);
}