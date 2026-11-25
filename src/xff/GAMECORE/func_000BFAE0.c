#ifdef NONMATCHING
/* 0 diffs: try_compilers reports MATCH? (166 words). Parked only because
   the splice can't place it yet: func_000BF880 is a GNU C nested function of
   this one (each call passes the static chain, sp, in v0, and func_000BF880
   stores it at sp+0; gcc emits a nested function before its parent, the
   Original order). The nested symbol (func_000BF880.0) has no Original name,
   so xff_splice refuses the jal to it. Needs splice support for nested
   functions, or func_000BF880 matched as the nested body. */
typedef struct {
    int name;
    int flag;
    int h;
    char pad[0x10];
} Weapon;

typedef struct {
    char pad[0x10];
    Weapon *list;
} WeaponList;

typedef struct {
    int active;
    float x;
    float y;
    float scale;
    float size;
    float rot;
    int visible;
    float alpha;
} WeaponSprite;

typedef struct {
    int a;
    int b;
    union {
        void *p;
        float f;
    } u;
} Item;

typedef struct {
    Item **items;
    int n;
} SprList;

extern int DldSysUndefSymbol;
extern char gcGlobalVar[];
extern WeaponList SH_WeaponListDEFAULT;
extern WeaponSprite B_0019CD48[9];
extern int D_0017B044;
extern int D_0017B048;
extern int _omakeSelectFlagChk(int);

#define GC_TIME (((struct { char pad[0x178]; float f; } *)gcGlobalVar)->f)

static inline int *dldTable(int *h)
{
    int off = *h & 0x3FFFF;
    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline int dldElem(int *h)
{
    int *t = dldTable(h);
    return t != 0 && t != (int *)DldSysUndefSymbol ? t[4] + ((*(unsigned *)h >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static void func_000BFAE0(SprList *spr)
{
    int idx;
    Weapon *list;
    int cur;
    int next;
    int prev;
    int i;
    float t;

    /* Stand-in body: the real one is the Parked draft in func_000BF880.c.
       It must write memory, or gcc treats the calls as pure and reschedules
       the loads around them. */
    void func_000BF880(char *obj, int idx, int unused, int val, float t)
    {
        *(char *)(obj + 0x4C) = val;
    }

    cur = D_0017B044 + 1;
    list = (DldSysUndefSymbol != (int)&SH_WeaponListDEFAULT ? &SH_WeaponListDEFAULT : 0)->list;
    for (i = 0; i < spr->n; i++)
        spr->items[i]->u.p = 0;
    spr->items[0]->u.f = 1.0f;
    if ((unsigned)(cur - 1) >= 9)
        return;

    next = cur;
    for (;;) {
        next++;
        if (next >= 10)
            next = 1;
        if (next == cur)
            break;
        if (_omakeSelectFlagChk(list[next].flag))
            break;
    }
    if (next == cur)
        next = -1;

    prev = cur;
    for (;;) {
        prev--;
        if (prev <= 0)
            prev = 9;
        if (prev == cur || prev == next)
            break;
        if (_omakeSelectFlagChk(list[prev].flag))
            break;
    }
    if (prev == cur || prev == next)
        prev = -1;

    for (i = 1; i < 10; i++) {
        int *o = (int *)dldElem(&list[i].h);
        void *p;
        idx = i - 1;
        p = (void *)o[0x14];
        t = GC_TIME - B_0019CD48[idx].alpha;
        if (t > 1.0f)
            t = 1.0f;
        if (i == cur)
            func_000BF880(p, idx, 1, 3, t);
        else if (i == prev)
            func_000BF880(p, idx, 0, i == D_0017B048 ? 2 : 1, t);
        else if (i == next)
            func_000BF880(p, idx, 2, i == D_0017B048 ? 2 : 1, t);
        else
            func_000BF880(p, idx, 3, 1, t);
    }
}
#endif
