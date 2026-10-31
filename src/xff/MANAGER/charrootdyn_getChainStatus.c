typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x40];
} GeometryPointer;

typedef struct {
    char pad0[0x50];
} ClipHit;

typedef struct {
    char pad0[0x78];
    float chainRadius;
} ChainParam;

typedef struct {
    char pad0[0x134];
    Vec4 *pos;
    char pad138[0x53C - 0x138];
    char noChain;
    char pad53D[0xDA0 - 0x53D];
    char parentInfo[0xDF0 - 0xDA0];
    void *group;
    char padDF4[0xE20 - 0xDF4];
    char clip[0x1140 - 0xE20];
    ChainParam *param;
} CharacterClass;

extern CharacterClass *GetCharacterClass(void *);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(void *, int);
extern int CheckClothChainDetect(GeometryPointer *, void *, Vec4 *, float);
extern void GetGeometryPointerPosition(Vec4 *, GeometryPointer *);
extern int ClipCollisionFinderCallBack(ClipHit *, Vec4 *, Vec4 *, void *, void *, int);
extern void CopyGeometryPointer(GeometryPointer *, GeometryPointer *);
extern void UnlinkSecureParentInfo(void *);
extern void LinkSecureParentInfoByGP(void *, GeometryPointer *);
extern int charrootdyn_slideExceptionJudgeCB();

static inline float vecDistSq(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

void charrootdyn_getChainStatus(void *self)
{
    GeometryPointer best;
    GeometryPointer gp;
    Vec4 pos;
    ClipHit hit;
    CharacterClass *cls;
    CharacterClass *c;
    float radius;
    float bestDist;
    float d;
    int found;
    void *o;
    int *g;

    cls = GetCharacterClass(self);
    radius = cls->param->chainRadius;
    if (!(0.0f < radius))
        return;
    bestDist = radius * radius;
    found = 0;
    o = 0;
    for (g = isysGroupForFirst(cls->group, 0); g != 0; g = isysGroupForNext(g, 0)) {
        o = (void *)*g;
        if (o == self)
            continue;
        c = GetCharacterClass(o);
        if (c != 0 && c->noChain != 0)
            continue;
        if (!CheckClothChainDetect(&gp, o, cls->pos, radius))
            continue;
        GetGeometryPointerPosition(&pos, &gp);
        d = vecDistSq(pos.f, cls->pos->f);
        if (!(d < bestDist))
            continue;
        if (ClipCollisionFinderCallBack(&hit, cls->pos, &pos, cls->clip, charrootdyn_slideExceptionJudgeCB, 0))
            continue;
        bestDist = d;
        found = 1;
        CopyGeometryPointer(&best, &gp);
    }
    if (o != 0)
        isysGroupForExit(o, 0);
    if (found) {
        UnlinkSecureParentInfo(cls->parentInfo);
        LinkSecureParentInfoByGP(cls->parentInfo, &best);
    }
}
