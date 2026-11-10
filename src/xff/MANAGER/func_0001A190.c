/* ~96 diffs, same length (105 words). Larger variant of func_00019FB8 (see that file): 0x220 bytes, packets at +0x20 / +0x120, header count 0x14, 10-quad copy of D_00135FB0, tags 0x6000000F / 0x6C0B8000 / 0x14000014, GS reg low words 800A and 8000. */
typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));
extern char rootPtn[];
extern s128 D_00135FB0[];
extern void *iosMallocAlign(void *, int, int);

#ifdef NONMATCHING
static void *func_0001A190(int arg)
{
    char *buf = iosMallocAlign(rootPtn, 0x220, 0x10);
    int i;
    int j;

    *(int *)(buf + 8) = (int)(buf + 0x20);
    *(int *)(buf + 0xC) = (int)(buf + 0x120);
    *(int *)buf = 0x14;
    *(int *)(buf + 4) = 0;
    for (i = 0; i < 2; i++) {
        char *p = *(char **)(buf + 8 + i * 4);
        s128 *src = D_00135FB0;
        s128 *dst;
        u64 a;
        u64 b;

        a = arg != 0 ? (u64)((arg << 7) | 4) : (u64)((arg << 7) | 0x44);
        b = arg != 0 ? (u64)((arg << 7) | 5) : (u64)((arg << 7) | 0x45);
        *(u64 *)(p + 0x40) = (a << 47) | 0x100040000000800AUL;
        *(u64 *)(p + 0) = 0x6000000FUL;
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
        *(int *)(p + 0x3C) = 0x6C0B8000;
        *(u64 *)(p + 0x48) = 0xDF00000004UL;
        *(u64 *)(p + 0x20) = (b << 47) | 0x1000400000008000UL;
        dst = (s128 *)(p + 0x50);
        for (j = 0; j < 10; j++)
            *dst++ = *src++;
        *(int *)dst = 0x22000014;
        dst = (s128 *)((char *)dst + 4);
        *(int *)dst = 0;
        dst = (s128 *)((char *)dst + 4);
        *(int *)((char *)dst + 4) = 0x10000000;
        *(int *)dst = 0;
    }
    return buf;
}
#endif
