/*meminit.c*/
#include <xos.h>

/**
 * TODO: Memory Manager: allocate memory to physical address and virtual addresses
 */
extern uint8 _end;
memblk_t *memptr; /* point to memory block */
/**
 * meminit() - Defines a freelist
 * Starts with some known memory range (e.g., after your kernel ends)
 * Sets up one large block of memory as the initial free region
 */
void mem_init(void){
    uint32 start = (uint32)&_end;

    // Align start to 8 bytes for safety
    if (start % 8 != 0) {
        start = (start + 7) & ~7;
    }
    
    uint32 end = 0x01000000;  // Assume 16 MB total RAM
    
    if (end <= start){
        memptr = NULL;
        return;
    }

    // Set up one big free block
    memptr = (memblk_t *)start;
    memptr->mnext = NULL;
    memptr->mlength = end - start;

    //terminal_writestring("Memory initialized. Usable bytes: ");
    char buf1[16];
    itoa(memptr->mlength, buf1);
    //terminal_writestring(buf1);
    //terminal_writestring("\n");

}

 /**
  * getmem(size) - Find first block that fits
  * Split if necessary
  * Remove from freelist
  */