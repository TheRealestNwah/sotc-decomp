typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void IirInit(char *pa0)
{
    *(int *)(pa0 + 0x1C) = 0;
    *(int *)(pa0 + 0x20) = 0;
    *(int *)(pa0 + 0x24) = 0;
    *(int *)(pa0 + 0x28) = 0;
    *(int *)(pa0 + 0x30) = 0;
    *(int *)(pa0 + 0x2C) = 0;
}
