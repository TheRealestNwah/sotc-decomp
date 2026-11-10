typedef unsigned long long u64;
typedef struct { u64 tag; u64 t2, t3, t4; unsigned int lo; unsigned int hi; } Layer;
typedef struct { int a, b; int adrs[2]; char *ptr; int e; int cur; int layer; } DlBufs;

extern DlBufs B_00065018;

/* Parked: 12 words differ (register allocation of the final tag merge). */
#ifdef NONMATCHING
void iosDlChainHeadCurrent(int tag)
{
    volatile DlBufs *dl = &B_00065018;
    int off = dl->layer * 0x30;
    volatile Layer *base = (Layer *)((char *)dl->adrs[dl->cur] + off);
    volatile char *node = dl->ptr;

    dl->ptr = dl->ptr + 0x20;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(node));
    *(volatile int *)(node + 0x1C) = 0;
    *(volatile u64 *)node = ((u64)tag << 32) | 0x50000000;
    *(volatile int *)(node + 0x18) = 0;
    *(volatile int *)(node + 0xC) = 0;
    *(volatile int *)(node + 8) = 0;
    *(volatile u64 *)(node + 0x10) = ((u64)((Layer *)base)->lo << 32) | 0x20000000;
    *(volatile int *)((char *)base + 0x20) = (int)node;
    { u64 t = ((Layer *)base)->tag; t = (t & 0x80000000FFFFFFFFull) | (((u64)(int)node << 32) & 0x7FFFFFFF00000000ull); t = (t & 0xFFFFFFFF8FFFFFFFull) | 0x50000000; ((Layer *)base)->tag = t; }

}
#else
extern void iosDlChainHeadCurrent(int tag);
#endif
