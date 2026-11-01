extern int *DldSysUndefSymbol;

typedef struct {
    char pad0[0x190];
    float f190;
} GcGlobalVar;
extern GcGlobalVar gcGlobalVar;

extern char *GetAnimationClass(void *);
extern char *GetCharacterClass(void *);
extern void arrowObjThrustParent(void *);
extern float iosGetRandom(void);

typedef struct {
    unsigned int h;
    float base;
    float rand;
    float min;
    float max;
} ThrustEnt;

typedef struct {
    char pad0[0xC];
    int count;
    ThrustEnt *e;
} ThrustTbl;

typedef struct {
    ThrustTbl *tbl;
    float timer;
} ThrustWork;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void updateArrowThrustWork(void *obj, ThrustWork *w)
{
    if (w->tbl) {
        int n = w->tbl->count;
        ThrustEnt *e = w->tbl->e;
        char *anim = GetAnimationClass(obj);
        char *cc = GetCharacterClass(obj);
        int i;
        for (i = 0; i < n; i++, e++) {
            if (*(char **)anim == dldResolve(&e->h)) {
                float f = *(float *)(anim + 8) * *(float *)(anim + 0x2C);
                if (*(signed char *)(cc + 0x360))
                    w->timer = 0;
                if (e->min <= f && (e->max <= 0.0f || f <= e->max)) {
                    if (w->timer <= 0.0f) {
                        arrowObjThrustParent(obj);
                        w->timer = e->base + e->rand * iosGetRandom();
                    }
                }
                w->timer -= gcGlobalVar.f190;
                return;
            }
        }
    }
}
