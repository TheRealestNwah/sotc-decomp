/* ~90 diffs, same length (98 words). Constants-only sibling of func_00018228 (see that file): 0x160-byte allocation, packet 2 at +0xC0, 4-quad copy from D_00135D30, 0x60000009 / 0x6C058000, GS reg low word 0x8004. */
typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));
extern char rootPtn[];
extern s128 D_00135D30[];
extern void *iosMallocAlign(void *, int, int);

#ifdef NONMATCHING
static void *func_000183F0(int arg)
{
    char *buf = iosMallocAlign(rootPtn, 0x160, 0x10);
    int i;
    int j;

    *(int *)(buf + 8) = (int)(buf + 0x20);
    *(int *)(buf + 0xC) = (int)(buf + 0xC0);
    *(int *)buf = 0;
    *(int *)(buf + 4) = 0;
    for (i = 0; i < 2; i++) {
        char *p = *(char **)(buf + 8 + i * 4);
        s128 *src = D_00135D30;
        s128 *dst;
        u64 a;
        u64 b;

        a = arg != 0 ? (u64)((arg << 7) | 2) : (u64)((arg << 7) | 0x42);
        b = arg != 0 ? (u64)((arg << 7) | 2) : (u64)((arg << 7) | 0x42);
        *(u64 *)(p + 0x40) = (a << 47) | 0x1000400000008004UL;
        *(u64 *)(p + 0) = 0x60000009UL;
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
        *(int *)(p + 0x3C) = 0x6C058000;
        *(u64 *)(p + 0x48) = 0xDF00000004UL;
        *(u64 *)(p + 0x20) = (b << 47) | 0x1000400000008002UL;
        dst = (s128 *)(p + 0x50);
        for (j = 0; j < 4; j++)
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
