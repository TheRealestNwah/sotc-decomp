typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

static void func_000C9BE0(char *pa0)
{
    *(int *)(pa0 + 0xBC) = 3;
    *(int *)(pa0 + 0xC0) = 0;
    *(int *)(pa0 + 0xC4) = 0;
    *(int *)(pa0 + 0xC8) = 0;
}
