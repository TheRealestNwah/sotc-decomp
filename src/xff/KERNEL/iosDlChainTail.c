typedef struct { int a, b; int adrs[2]; char *ptr; int e; int cur; } DlBufs;
typedef unsigned long long u64;

extern DlBufs B_00065018;

/* Parked: ~40 words differ (register allocation of node/base; same shape as iosDlChainHead). */
#ifdef NONMATCHING
void iosDlChainTail(int layer, int tag)
{
    volatile DlBufs *dl = &B_00065018;
    int *adrs = (int *)dl->adrs;
    volatile char *base = (char *)adrs[dl->cur] + layer * 0x30;
    volatile char *node = dl->ptr;
    volatile char *tail;
    u64 hi;

    dl->ptr = dl->ptr + 0x20;
    __asm__ __volatile__("pref 0, 0x40(%0)" : : "r"(node));
    *(volatile int *)(node + 0x1C) = 0;
    *(volatile u64 *)node = ((u64)tag << 32) | 0x50000000;
    *(volatile int *)(node + 0x18) = 0;
    *(volatile int *)(node + 0xC) = 0;
    *(volatile int *)(node + 8) = 0;
    tail = *(volatile char **)(base + 0x24);
    hi = (u64)(int)((u64)*(volatile unsigned int *)(tail + 0x14) & 0x7FFFFFFF) << 32;
    *(volatile u64 *)(node + 0x10) = hi | 0x20000000;
    tail = *(volatile char **)(base + 0x24);
    *(volatile u64 *)(tail + 0x10) = (*(volatile u64 *)(tail + 0x10) & 0x80000000FFFFFFFFull) | (((u64)(int)node & 0x7FFFFFFF) << 32);
    *(volatile char **)(base + 0x24) = node;
}
#else
extern void iosDlChainTail(int layer, int tag);
#endif
