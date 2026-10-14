typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void Init_TimeFVECTORInter(Vec4 *p, Vec4 *a, Vec4 *b, float x, float y)
{
    p[0].q = b->q;
    p[1].q = a->q;
    p[2].q = b->q;
    p[3].f[0] = x;
    p[3].f[1] = y;
}
