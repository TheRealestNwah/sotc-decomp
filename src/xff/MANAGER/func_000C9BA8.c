typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

static void func_000C9BA8(char *pa0)
{
    *(float *)(pa0 + 0xA4) = 1.0f;
    *(int *)(pa0 + 0xA0) = 0;
    *(int *)(pa0 + 0xA8) = 0;
}
