typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void ClipCollisionFinder(void *, Vec4 *, Vec4 *);
void charrootdyn_findGlobalYGeometryPoint(void *a, void *unused, Vec4 *p, float y)
{
    Vec4 t;
    t.q = p->q;
    t.f[1] += y;
    ClipCollisionFinder(a, p, &t);
}
