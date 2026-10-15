typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern int charrootdyn_slideExceptionJudgeCB();
extern int ClipCollisionFinderCallBack(void *, void *, Vec4 *, void *, void *, int);

int charrootdyn_getLandingSurface(void *f, void *a, void *b, Vec4 *pos, float y)
{
    Vec4 t;
    t.q = pos->q;
    t.f[1] += y;
    return ClipCollisionFinderCallBack(f, b, &t, a, charrootdyn_slideExceptionJudgeCB, 0) != 0;
}
