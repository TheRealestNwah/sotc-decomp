/* ~90 diffs, same length (98 words). Allocates and fills a pair of VIF/GIF packets (iosMallocAlign 0x180 bytes, header words 8/0xC point at the two 0xB0-byte packets): each packet gets the DMAtag-like words (0x6000000A, 0x10000000, 0x01000101, 0x6C0103A0, 0x6C068000), two GS-reg qwords whose value is ((arg << 7) | (arg ? 2 : 0x42)) << 47 | 0x10004000_0000800x, a 5-quad copy of D_00135CE0, and a 0x14000012 / 0x10000000 tail. Sibling func_000183F0 differs only in constants (0x160 bytes, 4 quads from D_00135D30, 0x60000009, 0x6C058000, reg low word 8004). The Original hoists all constants into $s/$t registers before the loop and computes (arg << 7) twice (once loop-invariant in $t1, once inside the loop for the movn), ours folds the two uses together and keeps constants inside. */
typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));
extern char rootPtn[];
extern s128 D_00135CE0[];
extern void *iosMallocAlign(void *, int, int);

#ifdef NONMATCHING
static void *func_00018228(int arg)
{
    char *buf = iosMallocAlign(rootPtn, 0x180, 0x10);
    int i;
    int j;

    *(int *)(buf + 8) = (int)(buf + 0x20);
    *(int *)(buf + 0xC) = (int)(buf + 0xD0);
    *(int *)buf = 0;
    *(int *)(buf + 4) = 0;
    for (i = 0; i < 2; i++) {
        char *p = *(char **)(buf + 8 + i * 4);
        s128 *src = D_00135CE0;
        s128 *dst;
        u64 a;
        u64 b;

        a = arg != 0 ? (u64)((arg << 7) | 2) : (u64)((arg << 7) | 0x42);
        b = arg != 0 ? (u64)((arg << 7) | 2) : (u64)((arg << 7) | 0x42);
        *(u64 *)(p + 0x40) = (a << 47) | 0x1000400000008005UL;
        *(u64 *)(p + 0) = 0x6000000AUL;
        *(int *)(p + 8) = 0x10000000;
        *(int *)(p + 0xC) = 0;
        *(int *)(p + 0x10) = 0;
        *(int *)(p + 0x14) = 0;
        *(int *)(p + 0x18) = 0x1000101;
        *(int *)(p + 0x1C) = 0x6C0103A0;
        *(u64 *)(p + 0x28) = 4;
        *(int *)(p + 0x30) = 0;
        *(int *)(p + 0x34) = 0;
        *(int *)(p + 0x38) = 0;
        *(int *)(p + 0x3C) = 0x6C068000;
        *(u64 *)(p + 0x48) = 0xDF00000004UL;
        *(u64 *)(p + 0x20) = (b << 47) | 0x1000400000008002UL;
        dst = (s128 *)(p + 0x50);
        for (j = 0; j < 5; j++)
            *dst++ = *src++;
        *(int *)dst = 0x14000012;
        dst = (s128 *)((char *)dst + 4);
        *(int *)dst = 0;
        dst = (s128 *)((char *)dst + 4);
        *(int *)((char *)dst + 4) = 0x10000000;
        *(int *)dst = 0;
    }
    return buf;
}
#endif
