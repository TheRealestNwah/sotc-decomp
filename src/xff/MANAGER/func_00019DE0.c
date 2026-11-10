#ifdef NONMATCHING
/* 96 diffs, 3 words longer. Draft from the asm; first of six sibling GS packet-set builders (func_00018228, func_000183F0, func_000185B8, func_00019DE0, func_00019FB8, func_0001A190: same frame shape, different constants and copy counts). Allocates 0x160 bytes from rootPtn, sets size 0x14 and two packet pointers (+0x20, +0xC0), then fills each packet with GIF tag 0x60000009, register words, a flag-dependent 64-bit value ((flag << 7 | 4 or 0x44) << 47 | 0x10004000_00008004, and the 5/0x45 variant), a 4-qword copy from D_00135F40 and the 0x14000014 trailer. Differences: the Original keeps all 64-bit constants in callee-saved registers (frame 0x50) and counts the qword copy up with sltiu (unsigned j < 4) while ours hoists fewer constants (frame 0x30) and rebuilds the copy loop. A match here would carry over to the other five. */
typedef int s128 __attribute__((mode(TI)));

extern char rootPtn[];
extern s128 D_00135F40[];
extern void *iosMallocAlign(void *, int, int);

typedef struct {
    int size;
    int zero;
    int *pkt[2];
} PktSet;

void *func_00019DE0(int flag)
{
    PktSet *set = iosMallocAlign(rootPtn, 0x160, 0x10);
    int i;

    set->size = 0x14;
    set->zero = 0;
    set->pkt[0] = (int *)((char *)set + 0x20);
    set->pkt[1] = (int *)((char *)set + 0xC0);
    for (i = 0; i < 2; i++) {
        char *p = (char *)set->pkt[i];
        s128 *src = D_00135F40;
        s128 *dst = (s128 *)(p + 0x50);
        unsigned int j;
        long a;
        long b;

        a = flag ? ((flag << 7) | 4) : ((flag << 7) | 0x44);
        b = flag ? ((flag << 7) | 5) : ((flag << 7) | 0x45);
        *(long *)(p + 0x40) = (a << 47) | 0x1000400000008004L;
        *(long *)(p + 0x0) = 0x60000009L;
        *(int *)(p + 8) = 0x10000000;
        *(int *)(p + 0xC) = 0;
        *(int *)(p + 0x10) = 0;
        *(int *)(p + 0x14) = 0;
        *(int *)(p + 0x18) = 0x1000101;
        *(int *)(p + 0x1C) = 0x6C0103A0;
        *(long *)(p + 0x28) = 4;
        *(int *)(p + 0x30) = 0;
        *(int *)(p + 0x34) = 0;
        *(int *)(p + 0x38) = 0;
        *(int *)(p + 0x3C) = 0x6C058000;
        *(long *)(p + 0x48) = 0xDF00000004L;
        *(long *)(p + 0x20) = (b << 47) | 0x1000400000008000L;
        for (j = 0; j < 4; j++)
            *dst++ = *src++;
        *(int *)(char *)dst = 0x14000014;
        *(int *)((char *)dst + 4) = 0;
        *(int *)((char *)dst + 8) = 0;
        *(int *)((char *)dst + 0xC) = 0x10000000;
    }
    return set;
}
#endif
