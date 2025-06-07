#include <os.h>

struct GDT {
    uint32 base;
    uint32 limit;
    uint8 access_byte;
    uint8 flags;
}__attribute__((packed));

void gdt_init(void);
//void encode_gdt_entry(uint8_t *target, struct GDT source);
void gdt_flush(uint32);
