extern int kickParticle(int, int, int, int, int);
extern void updateParticleGeo(int, int, int, int, int, int, int, int, int, int, void *, int);
extern void func_00091190(int, int, int, int);

static void func_00090D28(int a, int b, int c, int d, int e, int f)
{
    updateParticleGeo(0, a, b, c, 0, d, f, 0, e, 1, kickParticle, 0);
    func_00091190(a, d, e, f);
}
