typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void SetCollisionEdgeLinkDBFinderCollectStatus(char *pa0, int xa1, int xa2, char *pa3, int xt0, float f12)
{
    ((Vec4 *)(pa0 + 0x14))->i[0] = xa1;
    ((Vec4 *)(pa0 + 0x18))->f[0] = f12;
    *(char *)(pa0 + 0x12) = xa2;
    ((Vec4 *)(pa0 + 0x1C))->i[0] = xt0;
    ((Vec4 *)(pa0 + 0x0))->q = ((Vec4 *)(pa3 + 0x0))->q;
}
