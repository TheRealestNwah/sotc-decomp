typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void GetPlaneGlobalYFittingPoint(Vec4 *out, float *n, Vec4 *p)
{
    out->q = p->q;
    out->f[1] = -(n[0] * p->f[0] + n[2] * p->f[2] + n[3]) / n[1];
}
