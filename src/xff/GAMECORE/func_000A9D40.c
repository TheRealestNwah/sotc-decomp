typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x50];
    char frames[0xC];
    int fps;
} MotionResource;

typedef struct {
    char pad0[0x2C];
    float rate;
} MotionState;

typedef struct {
    char pad0[0x44];
    float speed;
} MotionCtrl;

typedef struct {
    char pad0[0x1C0];
    MotionState motion;
    char pad1F0[0xF50];
    MotionCtrl *ctrl;
} CharClass;

typedef struct {
    char pad0[0x14];
    float x14;
    char pad18[0xDC - 0x18];
    float xDC;
} KiteParam;

typedef struct {
    unsigned int h;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
} LayoutSheet;

typedef struct {
    unsigned int h;
    float x4;
} BaseSheet;

typedef struct {
    int type;
    char pad4[0x14];
    float x18;
    char pad1C[4];
    KiteParam *param;
    char pad24[0x31C - 0x24];
    float x31C;
    char pad320[0x470 - 0x320];
    char kite_layout[0x5F0 - 0x470];
    s128 pos;
    char pad600[0x7C0 - 0x600];
    float x7C0;
    char pad7C4[4];
    char surprised[0x800 - 0x7C8];
    char layout[0x10];
} KiteWork;

typedef struct {
    char pad0[0x48];
    unsigned int *sheet;
} ScriptClass;

extern int DldSysUndefSymbol;
extern int isysGetThisSubThread(void);
extern ScriptClass *GetScriptClass(int);
extern CharClass *GetCharacterClass(int);
extern int GetMotionResourceFrames(void *);
extern void AI_SetSurprisedArea(void *, float);
extern void AI_SetAnimalLayout(void *, s128 *, float, float);
extern void Kite_SetAnimalLayout(void *, s128 *, float, float, float);

static inline char *dld_ref(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol)
        ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)
        : 0;
}

static int func_000A9D40(KiteWork *w)
{
    int th = isysGetThisSubThread();
    unsigned int *h = GetScriptClass(th)->sheet;
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    BaseSheet *base = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(BaseSheet **)(t + 0x10) : 0;
    LayoutSheet *ls;
    MotionResource *res;

    if (base != 0) {
        ls = (LayoutSheet *)dld_ref(&base->h);
        w->x18 = base->x4;
        if (ls != 0) {
            res = (MotionResource *)dld_ref(&ls->h);
            AI_SetSurprisedArea(w->surprised, ls->x8);
            w->x7C0 = ls->x14;
            if (w->type == 8) {
                float b = ls->x10;
                float a = ls->xC;
                s128 v = w->pos;

                AI_SetAnimalLayout(w->layout, &v, a, b);
                b *= 0.5f;
                ((float *)&v)[1] += b * 0.5f;
                Kite_SetAnimalLayout(w->kite_layout, &v, a, b, w->param->x14);
            }
            if (res != 0) {
                CharClass *cls = GetCharacterClass(th);
                float speed = cls->ctrl->speed;
                MotionState *m = &cls->motion;
                float frames = GetMotionResourceFrames(res->frames);
                float rate = m->rate;
                float k = w->param->xDC;
                float lim = k > 1.0f ? 1.0f : k;

                w->x31C = frames * rate / (res->fps * speed) * lim;
                return 1;
            }
        }
    }
    return 0;
}
