typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct {
    char pad0[0xC];
    int flag;
    char pad10[0x40];
    short id;
} SObjNode;

typedef struct {
    char pad0[0x10];
    int *p10;
} ScriptWork;

typedef struct {
    int kind;
    char pad4[0x3C];
    float *rand40;
    char pad44[0xE0];
    float f124;
    int n128;
    int n12C;
    char pad130[4];
    int n134;
    int n138;
    char pad13C[4];
    float f140;
    char pad144[0x4C];
    int state;
    int next;
    char pad198[4];
    int n19C;
    int n1A0;
    char pad1A4[8];
    int n1AC;
    float f1B0;
    char pad1B4[0x14];
    int n1C8;
    char pad1CC[4];
    float f1D0;
    int n1D4;
    char pad1D8[8];
    Vec4 v1E0;
    Vec4 v1F0;
    float f200;
} GexWork;

extern int ControlMode_GEX_RE_FALL;
extern int ControlMode_GEX_RE_FALL_DEATH;
extern int ControlMode_GEX_RE_CUT_TAIL;
extern int ControlMode_GEX_RE_FALL_CUT_TAIL;
extern int isysGetThisSubThread(void);
extern float iosGetRandom(void);
extern float AI_GetInterRatioOutCut(float, float, float, float, float);
extern char *GetCharacterClass(int);
extern char *GetScriptCharacterClass(int);
extern char *GetLayoutClass(int);
extern void *memset(void *, int, unsigned int);
extern Vec4 *GetCollisionDBPlane(void *);
extern SObjNode *getSObjNode(int);
extern void gexsFlagSet(int, int);
extern void SetLayoutObjAccessSwitch(int, int);

static inline int isSteep(Vec4 *n)
{
    char *lay = GetLayoutClass(isysGetThisSubThread());
    memset(n, 0, sizeof(*n));
    n->f[1] = 1.0f;
    if (*(int *)(lay + 0x124) != 0)
        n->q = GetCollisionDBPlane(lay + 0xC0)->q;
    return n->f[1] <= 0.70710665f;
}

static inline int isReFall(int m)
{
    if (m == ControlMode_GEX_RE_FALL) return 1;
    if (m == ControlMode_GEX_RE_FALL_DEATH) return 1;
    if (m == ControlMode_GEX_RE_CUT_TAIL) return 1;
    return m == ControlMode_GEX_RE_FALL_CUT_TAIL;
}
static void func_000AFCE8(GexWork *w)
{
    Vec4 t;
    Vec4 n;
    int th;

    th = isysGetThisSubThread();
    if (w->state == w->next)
        return;
    w->n12C = 0;
    w->f200 = 1.0f;
    w->n128 = 0;
    switch (w->next) {
    case 1:
        if (w->state == 18)
            w->n138 = 0;
        w->f124 = w->rand40[1] + w->rand40[0] * iosGetRandom();
        break;
    case 2:
        w->n134 = 0;
        w->f124 = iosGetRandom() * 5.0f + 3.0f;
        break;
    case 4:
        w->f124 = AI_GetInterRatioOutCut(w->f140, 3.0f, 10.0f, 1.0f, 1.5f) * 5.0f;
        break;
    case 14:
        w->f124 = 1.5f / w->f1D0;
        break;
    case 16:
        w->f124 = AI_GetInterRatioOutCut(w->f140, 3.0f, 10.0f, 1.0f, 1.5f) * 5.0f;
        if (w->state == 18)
            w->n138 = 0;
        break;
    case 20:
        if (w->state == 18)
            w->n138 = 0;
        w->f124 = 5.0f / w->f1D0;
        break;
    case 17:
        w->f124 = 5.0f / w->f1D0;
        break;
    case 18:
        w->f124 = 5.0f / w->f1D0;
        break;
    case 19:
        w->f124 = 5.0f / w->f1D0;
        break;
    case 21:
        if (w->kind == 2)
            w->f124 = 5.0f;
        else
            w->f124 = 1.5f / w->f1D0;
        if (w->n1D4 != 0)
            t.q = w->v1E0.q;
        else
            t.q = w->v1F0.q;
        if (0.0f <= t.f[0])
            w->n19C = 7;
        else
            w->n19C = 6;
        break;
    case 22:
        w->f124 = 1.0f / w->f1D0;
        break;
    case 10:
        w->f124 = 30.0f;
        break;
    case 23:
        if (isReFall(*(int *)(GetCharacterClass(isysGetThisSubThread()) + 0x750))) {
            ScriptWork *sw = *(ScriptWork **)(GetScriptCharacterClass(th) + 0x1200);
            if (sw != 0 && sw->p10 != 0)
                *sw->p10 = 1;
        } else {
            w->n1A0 = 0x31;
        }
        break;
    case 26:
        if (isSteep(&n))
            w->n1A0 = 0x30;
        else
            w->n1A0 = 0x35;
        break;
    case 28:
        isysGetThisSubThread();
        w->n1AC = 1;
        w->n1C8 = 1;
        if (!isSteep(&n))
            w->n1A0 = 0x32;
        break;
    case 29: {
        int t2 = isysGetThisSubThread();
        SObjNode *o;
        w->f1B0 = *(float *)(*(char **)(GetLayoutClass(t2) + 0x134) + 4) + 0.03f;
        o = getSObjNode(t2);
        if (o != 0)
            gexsFlagSet(o->id, o->flag);
        break;
    }
    case 30:
        SetLayoutObjAccessSwitch(isysGetThisSubThread(), 0);
        break;
    }
}
