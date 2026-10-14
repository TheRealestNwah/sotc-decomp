typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void setAttainRangeData(char *pa0, char *pa1, float f12, float f13, float f14, float f15)
{
    *(s128 *)(pa0 + 0x3E0) = *(s128 *)(pa1 + 0x0);
    *(float *)(pa0 + 0x3F0) = f12;
    *(float *)(pa0 + 0x3F4) = f13;
    *(float *)(pa0 + 0x3F8) = f14;
    *(float *)(pa0 + 0x3FC) = f15;
}
