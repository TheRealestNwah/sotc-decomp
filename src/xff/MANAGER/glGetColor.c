typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern Vec4 D_00130510;

void glGetColor(Vec4 *c)
{
    c->q = D_00130510.q;
    c->f[0] *= 0.0039215688f;
    c->f[1] *= 0.0039215688f;
    c->f[2] *= 0.0039215688f;
    c->f[3] *= 0.0078125f;
}
