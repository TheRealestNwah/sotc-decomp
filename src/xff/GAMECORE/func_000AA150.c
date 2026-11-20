typedef int s128 __attribute__((mode(TI)));

extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void *SCRGetFirstObj(void *);
extern void scrRun(void);
extern void AI_InitAnimalOptimize(void *);
extern void AI_SetAnimalLayout(void *, void *, float, float);
extern void Kite_InitKitePathPoint(void *);
extern void Kite_InitEventCheck(void *);
extern int ControlMode_KITE_DEFAULT;
extern int ControlMode_KITE_TAKEOFF;
extern int ControlMode_KITE_FLY;
extern int ControlMode_KITE_SURFING;
extern int ControlMode_KITE_LANDING;
extern int ControlMode_KITE_DEATH;
extern s128 ZUnitVector;
extern s128 ZeroVector;
extern char gcGlobalVar[];

#define I(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define Q(p, o) (*(s128 *)((char *)(p) + (o)))

static inline void setZero(void *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
}

static inline void clearPair(int *v)
{
    v[0] = 0;
    v[1] = 0;
}

static inline void initLayout(char *q, s128 *pos)
{
    F(q, 0x18) = 1.0f;
    I(q, 0x8) = 0;
    I(q, 0x4) = 0;
    I(q, 0x0) = 0;
    I(q, 0xC) = 0;
    I(q, 0x10) = 0;
    I(q, 0x14) = 0;
    I(q, 0x1C) = 0;
    I(q, 0x20) = 0;
    I(q, 0x24) = 0;
    I(q, 0x28) = 1;
    Q(q, 0x50) = *pos;
    setZero(q + 0x60);
    setZero(q + 0x70);
    setZero(q + 0x80);
    setZero(q + 0x90);
    AI_SetAnimalLayout(q + 0x30, pos, 420.0f, 40.0f);
}

static void func_000AA150(char *p)
{
    void *th;
    char *lay;
    char *w;
    char *q;
    int mode;
    int sel;
    s128 v;

    th = isysGetThisSubThread();
    lay = GetLayoutClass(th);
    while ((I(p, 0x24) = (int)SCRGetFirstObj(gcGlobalVar + 0x2B0)) == 0)
        scrRun();
    AI_InitAnimalOptimize(p + 0x14);
    I(p, 0x268) = -1;
    I(p, 0x270) = -1;
    I(p, 0x274) = 9;
    I(p, 0x284) = 0x15;
    I(p, 0x3C) = 0x23;
    I(p, 0x7B8) = -1;
    I(p, 0x26C) = 0;
    I(p, 0x278) = 0;
    I(p, 0x27C) = 0;
    I(p, 0x288) = 1;
    I(p, 0x38) = 0;
    I(p, 0x40) = 0;
    I(p, 0x44) = 0;
    I(p, 0x798) = 1;
    I(p, 0x7A4) = 0;
    I(p, 0x7A8) = 0;
    I(p, 0x7B0) = 0;
    I(p, 0x2F4) = 0;
    I(p, 0x2F8) = 0;
    I(p, 0x2FC) = 0;
    I(p, 0x300) = 0;
    I(p, 0x320) = 0;
    I(p, 0x308) = 0;
    I(p, 0x304) = 0;
    I(p, 0x28C) = 0;
    I(p, 0x290) = 0;
    I(p, 0x294) = 0;
    I(p, 0x298) = 0;
    I(p, 0x29C) = 0;
    I(p, 0x2A0) = 0;
    I(p, 0x7B4) = 0;
    setZero(p + 0x2B0);
    setZero(p + 0x2C0);
    setZero(p + 0x2D0);
    I(p, 0x7C0) = 0;
    F(p, 0x30C) = 1.0f;
    F(p, 0x310) = 1.0f;
    F(p, 0x314) = 1.0f;
    F(p, 0x318) = 1.0f;
    w = GetLayoutClass((void *)I(p, 0x24));
    Q(p, 0x350) = **(s128 **)(w + 0x13C);
    Q(p, 0x330) = **(s128 **)(w + 0x134);
    setZero(p + 0x340);
    I(p, 0x324) = 0;
    I(p, 0x360) = 0;
    Kite_InitKitePathPoint(p + 0x600);
    Kite_InitKitePathPoint(p + 0x640);
    Kite_InitKitePathPoint(p + 0x680);
    Kite_InitKitePathPoint(p + 0x620);
    Kite_InitKitePathPoint(p + 0x660);
    Kite_InitEventCheck(p + 0x6A0);
    I(p, 0x580) = 0;
    I(p, 0x794) = 1;
    F(p, 0x588) = 1.0f;
    I(p, 0x584) = 0;
    I(p, 0x764) = 0;
    I(p, 0x790) = 0;
    I(p, 0x760) = 0;
    I(p, 0x58C) = 0;
    mode = I(GetCharacterClass(isysGetThisSubThread()), 0x750);
    if (mode == ControlMode_KITE_DEFAULT)
        sel = 0x1C;
    else if (mode == ControlMode_KITE_TAKEOFF)
        sel = 0x1D;
    else if (mode == ControlMode_KITE_FLY)
        sel = 0x1E;
    else if (mode == ControlMode_KITE_SURFING)
        sel = 0x1F;
    else if (mode == ControlMode_KITE_LANDING)
        sel = 0x20;
    else if (mode == ControlMode_KITE_DEATH)
        sel = 0x21;
    else
        sel = 0x1C;
    I(p, 0x260) = sel;
    Q(p, 0x230) = ZUnitVector;
    Q(p, 0x2E0) = ZeroVector;
    Q(p, 0x5D0) = ZeroVector;
    Q(p, 0x5E0) = ZeroVector;
    I(p, 0x7C4) = 1;
    I(p, 0x7BC) = 0;
    I(GetCharacterClass(th), 0x1170) = 0;
    v = **(s128 **)(lay + 0x134);
    Q(p, 0x5F0) = v;
    Q(p, 0x5A0) = v;
    Q(p, 0x5B0) = v;
    Q(p, 0x590) = v;
    Q(p, 0x620) = v;
    Q(p, 0x660) = v;
    Q(p, 0x600) = v;
    Q(p, 0x680) = v;
    Q(p, 0x780) = v;
    GetCharacterClass(th)[0xA25] = 1;
    initLayout(p + 0x7D0, (s128 *)(p + 0x5F0));
    q = p + 0x890;
    clearPair((int *)(q + 0x00));
    clearPair((int *)(q + 0x08));
    clearPair((int *)(q + 0x10));
    clearPair((int *)(q + 0x18));
    clearPair((int *)(q + 0x20));
    clearPair((int *)(q + 0x28));
    clearPair((int *)(q + 0x30));
    clearPair((int *)(q + 0x60));
    clearPair((int *)(q + 0x68));
    clearPair((int *)(q + 0x70));
    I(q, 0x38) = 1;
    I(q, 0x40) = 0;
    I(q, 0x3C) = 1;
    I(q, 0x44) = 0;
    setZero(q + 0x50);
    I(p, 0x48) = (int)th;
}
