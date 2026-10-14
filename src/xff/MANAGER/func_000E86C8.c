typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

static void func_000E86C8(char *pa0, int xa1, int xa2, int xa3, int xt0, int xt1)
{
    *(int *)(pa0 + 0x0) = xa1;
    *(int *)(pa0 + 0x4) = xa2;
    *(long *)(pa0 + 0x8) = xa3;
    *(int *)(pa0 + 0x10) = xt0;
    *(int *)(pa0 + 0x14) = xt1;
}
