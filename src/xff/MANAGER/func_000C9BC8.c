typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

static void func_000C9BC8(char *pa0)
{
    *(float *)(pa0 + 0xB4) = 1.0f;
    *(int *)(pa0 + 0xB0) = 0;
    *(int *)(pa0 + 0xB8) = 0;
}
