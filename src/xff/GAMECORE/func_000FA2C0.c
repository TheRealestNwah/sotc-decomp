typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

static void func_000FA2C0(char *pa0)
{
    *(int *)(pa0 + 0x40) = -1;
    *(s128 *)(pa0 + 0x30) = *(s128 *)(pa0 + 0x0);
    *(s128 *)(pa0 + 0x50) = *(s128 *)(pa0 + 0x0);
}
