typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void charrootdyn_getForceLimitMode(char *pa0, char *pa1)
{
    ((Vec4 *)(pa0 + 0x0))->i[0] = 2;
    ((Vec4 *)(pa0 + 0x4))->f[0] = 1.5707963f;
    ((Vec4 *)(pa0 + 0x8))->i[0] = ((Vec4 *)(pa1 + 0xC30))->i[0];
}
