typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *GetCharacterClass(void *);
extern int ClipCollisionFinderCallBack(void *, Vec4 *, Vec4 *, char *, void *, int);
extern int charrootdyn_slideExceptionJudgeCB();
extern void ParentLayoutObj(void *, void *);
extern void func_0005DB18(void *);

void charrootdyn_resetRootDynamicsWithLowerCollisionForXZFit(void *o)
{
    char buf[0x50] __attribute__((aligned(16)));
    Vec4 p;
    char *c = GetCharacterClass(o);
    Vec4 *pos = *(Vec4 **)(c + 0x134);
    p.q = pos->q;
    p.f[1] += -1.0f;
    if (ClipCollisionFinderCallBack(buf, pos, &p, c + 0xE20, charrootdyn_slideExceptionJudgeCB, 0))
        ParentLayoutObj(o, buf);
    func_0005DB18(o);
}
