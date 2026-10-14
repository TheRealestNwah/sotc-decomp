typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void SetGeometryPointerGlobalState(char *pa0, char *pa1, char *pa2)
{
    ((Vec4 *)(pa0 + 0x30))->i[0] = 0;
    ((Vec4 *)(pa0 + 0x0))->q = ((Vec4 *)(pa1 + 0x0))->q;
    ((Vec4 *)(pa0 + 0x10))->q = ((Vec4 *)(pa2 + 0x0))->q;
}
