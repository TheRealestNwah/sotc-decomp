typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void initInterestWork(int xa0, char *pa1)
{
    *(int *)(pa1 + 0x8) = -1;
    *(int *)(pa1 + 0x0) = 0;
    *(int *)(pa1 + 0x4) = 0;
    *(int *)(pa1 + 0xC) = 0;
}
