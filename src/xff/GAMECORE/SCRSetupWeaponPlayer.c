typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern char ZeroPoint[], IdentityQuaternion[];
typedef struct { int name; char pad[0xC]; int h; char pad2[8]; } Weapon;
typedef struct { char pad[0x10]; Weapon *list; } WeaponList;
extern WeaponList SH_WeaponListDEFAULT;
typedef struct { int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o; } MParam;
extern void *initScriptLayoutObj(Ptn *, int, MParam *, int, int, void *, int);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern void SetGeometryPointerNodePosState(void *, void *, int, void *, void *);
extern void GetMotionNodeQuaternionPosToolCoord(float *, float *, void *, int, int);
extern void FlushCollisionWork(void *);
extern void player_setWeaponScriptSwitch(void *, Weapon *);

static inline int *dldTable(int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline int dldElem(int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[4] + ((*(unsigned *)h >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void *SCRSetupWeaponPlayer(void *obj, int idx)
{
    char geo[0x40] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    void *o = 0;
    Weapon *list;

    SetGeometryPointerNodePosState(geo, obj, 0x10000, IdentityQuaternion, ZeroPoint);
    GetMotionNodeQuaternionPosToolCoord(q, pos, obj, 0x10000, 0);
    list = (DldSysUndefSymbol != (int)&SH_WeaponListDEFAULT ? &SH_WeaponListDEFAULT : 0)->list;
    if (dldElem(&list[idx].h) != 0) {
        MParam s;

        s.a = 0;
        s.b = (int)ZeroPoint;
        s.c = (int)IdentityQuaternion;
        s.d = 0;
        s.i = (int)geo;
        s.e = 0;
        s.f = 0;
        s.g = 0;
        s.h = 1;
        s.j = 0;
        s.k = 0;
        s.l = 1;
        s.m = 0;
        s.n = 0;
        s.o = 0;
        o = initScriptLayoutObj(&rootPtn, dldElem(&list[idx].h), &s, idx, 4, obj, 0);
        if (o != 0) {
            isysAddGroupWithLinkParam(o, gcGlobalVar + 0x280, 0, 0);
            FlushCollisionWork(o);
        }
    }
    player_setWeaponScriptSwitch(obj, &list[idx]);
    return o;
}
