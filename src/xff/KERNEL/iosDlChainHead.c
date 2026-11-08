typedef struct { int a, b; int adrs[2]; char *ptr; int e; int cur; } DlBufs;
typedef unsigned long long u64;

extern DlBufs B_00065018;

/* Parked: 46 words differ (register allocation of the node/base pointers; volatile accesses already match in order). */
#ifdef NONMATCHING
void iosDlChainHead(int layer, int tag)
{
    volatile DlBufs *dl = &B_00065018;
    int *adrs = (int *)dl->adrs;
    volatile char *base = (char *)adrs[dl->cur] + layer * 0x30;
    volatile char *node = dl->ptr;

    dl->ptr = dl->ptr + 0x20;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(node));
    *(volatile int *)(node + 0x1C) = 0;
    *(volatile u64 *)node = ((u64)tag << 32) | 0x50000000;
    *(volatile int *)(node + 0x18) = 0;
    *(volatile int *)(node + 0xC) = 0;
    *(volatile int *)(node + 8) = 0;
    *(volatile u64 *)(node + 0x10) = ((u64)*(volatile unsigned int *)(base + 0x20) << 32) | 0x20000000;
    *(volatile int *)(base + 0x20) = (int)node;
    *(volatile u64 *)base = ((((*(volatile u64 *)base & 0x80000000FFFFFFFFull) | (((u64)(int)node << 32) & 0x7FFFFFFF00000000ull)) & 0xFFFFFFFF8FFFFFFFull) | 0x50000000);
}
#else
extern void iosDlChainHead(int layer, int tag);
#endif
