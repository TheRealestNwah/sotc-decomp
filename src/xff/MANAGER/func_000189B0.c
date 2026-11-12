/* Parked draft (~99 diffs): two-buffer GIF display list of 12 quad strips copied from the D_00135DC0 table.
   The original keeps 2/0x42/4 and the GIF tag key in s-regs, ORs before the <<47 shift (ours folds the
   shift into the select), and stores the STCYCL word through a stack slot (volatile cyc here). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef long s64;

extern char rootPtn[];
extern s128 D_00135DC0[];
extern void *iosMallocAlign(char *, int, int);

static void *func_000189B0(s64 arg)
{
    char *list = iosMallocAlign(rootPtn, 0x6A0, 0x10);
    int *hdr = (int *)list;
    char **slot;
    int buf;
    volatile int cyc;
    s64 key = (0x10004000L << 0x20) | 0x8002;
    s64 four = 4;

    cyc = 0x01000000;
    hdr[0] = 8;
    hdr[2] = (int)(list + 0x20);
    hdr[3] = (int)(list + 0x360);
    hdr[1] = 0;
    slot = (char **)(list + 8);
    cyc |= 0x101;
    for (buf = 0; buf < 2; buf++) {
        char *p = *slot;
        s128 *src;
        char *w;
        int i;

        *(int *)(p + 0xC) = 0;
        *(s64 *)(p + 0x20) = ((arg != 0 ? (arg << 7) | 2 : (arg << 7) | 0x42) << 0x2F) | key;
        *(s64 *)(p + 0x0) = 0x60000033;
        *(int *)(p + 0x8) = 0x10000000;
        *(int *)(p + 0x10) = 0;
        *(int *)(p + 0x14) = 0;
        *(int *)(p + 0x1C) = 0x6C0103A0;
        *(int *)(p + 0x18) = cyc;
        *(s64 *)(p + 0x28) = four;
        *(int *)(p + 0x30) = 0;
        *(int *)(p + 0x34) = 0;
        *(int *)(p + 0x38) = 0;
        *(int *)(p + 0x3C) = 0x6C038000;
        w = p + 0x40;
        src = D_00135DC0;
        for (i = 0; i < 0xC; i++) {
            *(s64 *)w = ((arg != 0 ? (arg << 7) | 2 : (arg << 7) | 0x42) << 0x2F) | key;
            w += 8;
            *(s64 *)w = (0xDF00L << 0x18) | four;
            w += 8;
            *(s128 *)w = src[0];
            w += 0x10;
            *(s128 *)w = src[1];
            w += 0x10;
            src += 2;
            *(int *)w = 0x14000012;
            w += 4;
            *(int *)w = 0;
            w += 4;
            *(int *)w = 0;
            w += 4;
            *(int *)w = i != 0xB ? 0x6C038000 : 0x10000000;
            w += 4;
        }
        slot += 1;
    }
    return list;
}
#endif
