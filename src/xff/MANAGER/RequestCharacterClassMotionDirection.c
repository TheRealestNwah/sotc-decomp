typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void RequestCharacterClassMotionDirection(char *p, Vec4 *v)
{
    ((Vec4 *)(p + 0xC50))->i[1] = 1;
    ((Vec4 *)(p + 0xC70))->q = v->q;
}
