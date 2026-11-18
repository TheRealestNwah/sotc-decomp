/* Parked attempt: 5 diffs. The Original sets s2 = &func_000DDA00 in the
 * prologue and tests cbMode in v1; this version computes it in v1 and copies
 * it to s2 in the beqz delay slot (cbMode in a0). */
#ifdef NONMATCHING
extern int *DldSysUndefSymbol;
static void func_000DD938(void);
static void func_000DDA00(void);
static void func_000DDB08(void);
static void func_000DDC08(void);
static void func_000DDD78(void);
static void func_000DDDE0(void);
extern char *sndSepReq(void *, void *, void *, void *, void *, int, int);
extern void *sndSepPlayerSrh(int, int, int);
extern void *sndSepPlayerSrh2(int, int);
extern void sndSepStopReq(void *);
extern void (*D_00139E6C)(char *);
extern int B_001502E0;
extern int B_001502E4;
extern int B_001502E8;

typedef struct {
    unsigned int ch : 5;
    unsigned int prog : 7;
    unsigned int pad12 : 2;
    unsigned int cbMode : 2;
    unsigned int kind : 2;
    unsigned int pad18 : 14;
} SeFlags;

typedef struct Se3D {
    char pad0[4];
    unsigned int link;
    SeFlags f;
} Se3D;

typedef struct {
    char pad0[0xC];
    int stride;
} SymTab;

typedef struct {
    char pad0[4];
    int bank;
} SndBank;

typedef struct {
    char pad0[0x1C];
    SndBank *snd;
} SymObj;

typedef struct {
    char pad0[8];
    SymTab *tab;
    char padC[4];
    char *base;
} SymMod;

static inline char *sepReq(void *f1, void *f2, void *f3, void *f4, int u, Se3D *id)
{
    if ((int)id == u)
        return 0;
    return sndSepReq(f1, f2, f3, id, f4, 0, 0);
}

static inline void *selCb(Se3D *se, void *cb)
{
    if (se->f.cbMode == 0)
        return cb;
    if (se->f.cbMode == 1)
        return func_000DDC08;
    return func_000DDB08;
}

char *sePlay3D(Se3D *se, int a, int b, int c)
{
    void *cb = selCb(se, func_000DDA00);
    char *ret;

    B_001502E0 = a;
    B_001502E4 = b;
    B_001502E8 = c;
    if (se->f.kind != 0) {
        unsigned int *lp = &se->link;
        unsigned int l = *lp;
        SymMod *m;
        SymObj *o;
        if ((l & 0x3FFFF) != 0)
            m = *(SymMod **)((char *)lp - (l & 0x3FFFF));
        else
            m = 0;
        if (m != 0 && m != (SymMod *)DldSysUndefSymbol)
            o = (SymObj *)(m->base + ((l >> 18) & 0xFFF) * m->tab->stride);
        else
            o = 0;
        if (o != 0) {
            if (se->f.kind != 2) {
                void *h = sndSepPlayerSrh(o->snd->bank, se->f.ch, se->f.prog);
                if (h != 0) {
                    if ((*(unsigned short *)((char *)se + 0xA) & 3) == 1)
                        return 0;
                    sndSepStopReq(h);
                }
            } else {
                if (sndSepPlayerSrh2(o->snd->bank, se->f.ch) != 0)
                    return 0;
            }
        }
    }
    ret = sepReq(func_000DD938, cb, func_000DDDE0, func_000DDD78, *DldSysUndefSymbol, se);
    if (D_00139E6C != 0 && ret != 0)
        D_00139E6C(ret);
    return ret;
}
#else
typedef struct Se3D Se3D;
extern char *sePlay3D(Se3D *se, int a, int b, int c);
#endif
