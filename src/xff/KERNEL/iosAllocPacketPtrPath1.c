typedef struct {
    int a, b;
    int adrs[2];
    int ptr;
    int e;
    int cur;
} DlBufs;

extern volatile DlBufs B_00065018;

/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
int iosAllocPacketPtrPath1(int size)
{
    volatile DlBufs *dl = &B_00065018;
    int p = dl->ptr;

    dl->ptr = dl->ptr + size;
    __asm__ __volatile__("pref 0, 0x40(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(p));
    return p;
}
