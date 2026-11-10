/* ~94 diffs, same length (100 words). VIF packet allocator in the func_00018228 family (see that park): 0x180 bytes, header count 4, two 0xB0-byte packets, 5-quad copy of D_00135D70 (the Original counts the copy down from 4 with bgez, unlike func_00018228), same constants and GS regs as func_00018228. Same register-allocation diffs as the family. */
typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));
extern char rootPtn[];
extern s128 D_00135D70[];
extern void *iosMallocAlign(void *, int, int);

#ifdef NONMATCHING
static void *func_000185B8(int arg)
{
    char *buf = iosMallocAlign(rootPtn, 0x180, 0x10);
    int i;
    int j;

    *(int *)(buf + 8) = (int)(buf + 0x20);
    *(int *)(buf + 0xC) = (int)(buf + 0xD0);
    *(int *)buf = 4;
    *(int *)(buf + 4) = 0;
    for (i = 0; i < 2; i++) {
        char *p = *(char **)(buf + 8 + i * 4);
        s128 *src = D_00135D70;
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
        for (j = 4; j >= 0; j--)
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
