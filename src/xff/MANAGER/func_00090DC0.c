extern int kickParticle(int, int, int, int, int);
extern void updateParticleDissolveGeo(int, int, int, int, int, int, int, int, int, int, void *, int);
extern void func_00091190(int, int, int, int);

static void func_00090DC0(int a, int b, int c, int d, int e, int f)
{
    updateParticleDissolveGeo(0, a, b, c, 0, d, f, 0, e, 1, kickParticle, 0);
    func_00091190(a, d, e, f);
}
