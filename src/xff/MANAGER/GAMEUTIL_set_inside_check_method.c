typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void GAMEUTIL_set_inside_check_method(Vec4 *p, int m, Vec4 *v)
{
    p[0].i[0] = m;
    p[1].q = v->q;
}
