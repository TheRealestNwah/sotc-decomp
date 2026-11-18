typedef int s128 __attribute__((mode(TI)));
extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char *GetScriptAnimationGlobalBaseInfo(void);
extern char *getSCRDataCtrlWork(void *);
extern int SCRGetFirstObj(void *);
extern char *GetLayoutClass(int);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern void glColor4f(float, float, float, float);
extern int ClipCollisionDirectCallBackDoubleSide(void *, void *, void *, void *, int, int, int, int, int, int);
extern void SendDamageLetter(int, int, char *, void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline int dldCount(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;
}

static inline float dist(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

void SCRFuncCheckBoneColAndSendDamage(void *actor, int b, int c, int d, int e, unsigned int *bones, unsigned int *target, float damage, float radius)
{
    s128 tpos[1];
    float p0[4];
    float p1[4];
    float q[4];
    char col[0x50];
    union { s128 q; float f[4]; } dmg;
    char *info;
    char *work;
    unsigned int *list;
    int n;
    int obj;
    int j;
    float len;
    void *pp;

    info = GetScriptAnimationGlobalBaseInfo();
    work = getSCRDataCtrlWork(actor);
    list = (unsigned int *)dldResolve(bones);
    n = dldCount(bones);
    obj = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    if (obj != 0)
        tpos[0] = **(s128 **)(GetLayoutClass(obj) + 0x134);
    else
        tpos[0] = **(s128 **)(*(char **)(work + 0x407C) + 0x134);
    for (j = 0; j < n - 1; j++) {
        char *b0 = dldResolve(&list[j]);
        char *b1 = dldResolve(&list[j + 1]);
        GetMotionNodeQuaternionPos(q, p0, actor, *(int *)(b0 + 8), 1);
        GetMotionNodeQuaternionPos(q, p1, actor, *(int *)(b1 + 8), 1);
        len = dist(p0, p1) + radius;
        pp = *(void **)(*(char **)(work + 0x407C) + 0x134);
        if (dist(p0, pp) < len || dist(p1, pp) < len || dist(p0, tpos) < len || dist(p1, tpos) < len) {
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            if (ClipCollisionDirectCallBackDoubleSide(col, p0, p1, gcGlobalVar + 0x238, 1, 0, 0, 0, 0, 0)) {
                dmg.q = *(s128 *)(col + 0x40);
                dmg.f[3] = damage;
                SendDamageLetter(0, *(int *)(info + 8), dldResolve(target), &dmg);
                glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
            }
        }
    }
}
