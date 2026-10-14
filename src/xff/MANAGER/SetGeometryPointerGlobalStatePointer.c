typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void SetGeometryPointerGlobalStatePointer(Vec4 *p, int a, int b, Vec4 *u, Vec4 *v)
{
    p[0].i[0] = a;
    p[3].i[0] = 6;
    p[0].i[1] = b;
    p[1].q = u->q;
    p[2].q = v->q;
}
