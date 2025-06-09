/* memory.h */

/* define memory block */
typedef struct memblk {
    struct memblk *mnext;    /* pointer points to next free memory block */
    uint32 mlength;          /* Size of the block including memblk */
}memblk_t;