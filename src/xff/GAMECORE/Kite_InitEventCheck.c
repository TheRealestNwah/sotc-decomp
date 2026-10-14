typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void Kite_InitEventCheck(char *pa0)
{
    *(int *)(pa0 + 0x0) = -1;
    *(int *)(pa0 + 0x4) = 0;
    *(int *)(pa0 + 0x8) = 0;
    *(int *)(pa0 + 0xC) = 0;
}
