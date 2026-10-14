typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void SetGeometryPointerChainPos(char *pa0, int xa1, int xa2, float f12)
{
    *(int *)(pa0 + 0x30) = 9;
    *(int *)(pa0 + 0x0) = xa1;
    *(int *)(pa0 + 0x4) = xa2;
    *(float *)(pa0 + 0x8) = f12;
}
