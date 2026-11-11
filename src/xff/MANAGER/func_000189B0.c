/* Parked draft: two-buffer GIF display list of 12 quad strips copied from the D_00135DC0 table.
   Written from the m2c draft; not yet compared closely. */
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
    s64 key = (0x10004000L << 0x20) | 0x8002;

    hdr[0] = 8;
    hdr[2] = (int)(list + 0x20);
    hdr[3] = (int)(list + 0x360);
    hdr[1] = 0;
    slot = (char **)(list + 8);
    for (buf = 0; buf < 2; buf++) {
        char *p = *slot;
        s128 *src = D_00135DC0;
        int *w;
        int i;

        *(int *)(p + 0xC) = 0;
        *(s64 *)(p + 0x20) = (((arg << 7) | (arg != 0 ? 2 : 0x42)) << 0x2F) | key;
        *(int *)(p + 0x0) = 0x60000033;
        *(int *)(p + 0x8) = 0x10000000;
        *(int *)(p + 0x10) = 0;
        *(int *)(p + 0x14) = 0;
        *(int *)(p + 0x1C) = 0x6C0103A0;
        *(int *)(p + 0x18) = 0x01000101;
        *(int *)(p + 0x28) = 4;
        *(int *)(p + 0x30) = 0;
        *(int *)(p + 0x34) = 0;
        *(int *)(p + 0x38) = 0;
        *(int *)(p + 0x3C) = 0x6C038000;
        w = (int *)(p + 0x40);
        for (i = 0; i < 0xC; i++) {
            *(s64 *)w = (((arg << 7) | (arg != 0 ? 2 : 0x42)) << 0x2F) | key;
            *(s64 *)(w + 2) = (0xDF00L << 0x18) | 4;
            *(s128 *)(w + 4) = src[0];
            *(s128 *)(w + 8) = src[1];
            src += 2;
            w[12] = 0x14000012;
            w[13] = 0;
            w[14] = 0;
            w[15] = (i ^ 0xB) != 0 ? 0x6C038000 : 0x10000000;
            w += 16;
        }
        slot += 1;
    }
    return list;
}
#endif
