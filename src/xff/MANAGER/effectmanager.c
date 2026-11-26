typedef struct Ptn Ptn;
typedef struct {
    int unknown;
    signed int priority : 28;
    unsigned int flags : 4;
    char rest[88];
} FsEffect;
typedef struct {
    char bytes[96];
} FsEffectBytes;
typedef struct {
    FsEffect *effect;
    const signed char *playMode;
} EffectStart;
typedef struct FsEffectDemoParam {
    int pad0;
    unsigned int effect;
    unsigned int sub;
} FsEffectDemoParam;
typedef struct FsEffectState {
    FsEffect *effect;
    void *sub;
} FsEffectState;
typedef struct {
    char pad0[0x10];
    FsEffect *effect;
} FsEffectOwner;
typedef struct {
    int enabled;
    float nearDist;
    float farDist;
    float nearRate;
    float farRate;
    int r;
    int g;
    int b;
    int offset;
} FogParam;
typedef struct {
    char pad[0x10];
    FogParam *fog;
} FogEffect;

extern Ptn rootPtn;
extern FsEffectState D_001303E0;
extern int D_001303E4;
extern void *DldSysUndefSymbol;
extern const char RO_0013C920[];
extern char SH_FsEffectDEFAULT[];
extern FsEffect B_00147310;
extern FsEffect *FsEffect_RESET;
extern FsEffect *FsEffect_DEFAULT;
extern void *iosMallocAlign(Ptn *, int, int);
extern void iosFree(int);
extern void isysSleepSubThread(void);
extern void *createScriptObj(void *, int, Ptn *, int, int, int, int, int);
extern void SetScriptObjDeleteCallBackFunc(void *, int, int);
extern void iosLocalPrintf(const char *, ...);
extern void *memcpy(void *, const void *, unsigned int);
extern void skipBlur(int);
extern int solarFlareReset();
extern float *getFogNearDist(void);
extern float *getFogFarDist(void);
extern float *getFogNearRate(void);
extern float *getFogFarRate(void);
extern int *getFogColorR(void);
extern int *getFogColorG(void);
extern int *getFogColorB(void);
extern int *getFogOffset(void);
extern void changeFogParam(void);

void fsEffectDefault(void);
static void func_0000DFF8(void);
static void func_0000E058(FsEffect *effect);
static void T_0000E0B0(EffectStart *);

static inline void selectEffect(FsEffect *effect)
{
    if (effect && (!D_001303E0.effect || effect->priority >= D_001303E0.effect->priority))
        D_001303E0.effect = effect;
}

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline void *resolveSymbolData(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module;

    if (offset) {
        module = *(char **)((char *)reference - offset);
    } else {
        module = 0;
    }
    if (module && module != DldSysUndefSymbol) {
        return *(void **)(module + 0x10);
    }
    return 0;
}

static inline void fsEffectRequest(FsEffect *effect)
{
    if (effect != 0) {
        if (D_001303E0.effect == 0) {
            D_001303E0.effect = effect;
        } else if (effect->priority >= D_001303E0.effect->priority) {
            D_001303E0.effect = effect;
        }
    }
}

static inline void fsEffectRequestReset(FsEffect *effect)
{
    if (effect != 0) {
        if (D_001303E0.effect == 0 || !(effect->priority < D_001303E0.effect->priority)) {
            D_001303E0.effect = effect;
        }
    }
}

static inline void setFsEffect(FsEffect *e)
{
    if (e != 0) {
        memcpy(&B_00147310, e, 0x60);
    }
}

void fsEffectSetParamSheetSeg(unsigned int *reference)
{
    FsEffect *effect = (FsEffect *)resourceData(reference);
    if (effect && (!D_001303E0.effect ||
        effect->priority >= D_001303E0.effect->priority))
        D_001303E0.effect = effect;
}

void fogEffectSetParam(int arg0)
{
    D_001303E4 = arg0;
}

void effectReset(void)
{
    int *p = (int *)&D_001303E0;

    p[0] = 0;
    p[1] = 0;
    fsEffectDefault();
}

void *fsEffectCreateSetScript(int a, int b, int c)
{
    void *o = createScriptObj(func_0000E058, c, &rootPtn, 0x1800, 0, 8, b, 0);
    if (o != 0)
        SetScriptObjDeleteCallBackFunc(o, (int)func_0000DFF8, c);
    return o;
}

void *fsEffectCreateSetScriptSheetSeg(int unused, int b, unsigned int *reference)
{
    char *effect = resourceData(reference);
    if (effect) {
        void *object = createScriptObj(func_0000E058, (int)effect, &rootPtn, 0x1800, 0, 8, b, 0);
        if (object)
            SetScriptObjDeleteCallBackFunc(object, (int)func_0000DFF8, (int)effect);
        return object;
    }
    iosLocalPrintf(RO_0013C920, 0x1EE);
    return 0;
}

void *fsEffectCreateSetScriptWithPlayMode(int unused, int priority, FsEffect *effect, const signed char *playMode)
{
    EffectStart *start = iosMallocAlign(&rootPtn, sizeof(EffectStart), 16);
    void *object;
    start->playMode = playMode;
    start->effect = effect;
    object = createScriptObj(T_0000E0B0, (int)start, &rootPtn, 0x1800, 0, 8, priority, 0);
    if (object)
        SetScriptObjDeleteCallBackFunc(object, (int)func_0000DFF8, (int)effect);
    return object;
}

void fsEffectManagerSetDemoParam(FsEffectDemoParam *param)
{
    FsEffect *effect = resolveSymbolData(&param->effect);
    void *sub = resolveSymbolData(&param->sub);

    if (effect) {
        if (D_001303E0.effect == 0 || effect->priority >= D_001303E0.effect->priority) {
            D_001303E0.effect = effect;
        }
    }
    D_001303E0.sub = sub;
}

int fsEffectReset(void)
{
    skipBlur(1);
    return solarFlareReset();
}

void fsEffectDefault(void)
{
    char *s = (char *)DldSysUndefSymbol != SH_FsEffectDEFAULT ? SH_FsEffectDEFAULT : 0;

    if (s != 0) {
        fsEffectRequest(&B_00147310);
    }
}

void fsEffectManagerInit(void)
{
    if (FsEffect_DEFAULT)
        *(FsEffectBytes *)&B_00147310 = *(FsEffectBytes *)FsEffect_DEFAULT;
}

void initFsEffect(FsEffectOwner *owner)
{
    if (((unsigned int *)owner->effect)[1] & 0xF0000000) {
        setFsEffect(owner->effect);
    }
    setFsEffect(FsEffect_DEFAULT);
}

void deleteFsEffect(void)
{

}

void initFogEffect(FogEffect *effect)
{
    FogParam *fog = effect->fog;

    if (fog->enabled == 0) {
        return;
    }
    if (fog->nearDist != -1.0f) {
        *getFogNearDist() = fog->nearDist;
    }
    if (fog->farDist != -1.0f) {
        *getFogFarDist() = fog->farDist;
    }
    if (fog->nearRate != -1.0f) {
        *getFogNearRate() = fog->nearRate;
    }
    if (fog->farRate != -1.0f) {
        *getFogFarRate() = fog->farRate;
    }
    if (fog->r != -1) {
        *getFogColorR() = fog->r;
    }
    if (fog->g != -1) {
        *getFogColorG() = fog->g;
    }
    if (fog->b != -1) {
        *getFogColorB() = fog->b;
    }
    if (fog->offset != -1) {
        *getFogOffset() = fog->offset;
    }
    changeFogParam();
}

void deleteFogEffect(void)
{

}

int getCurrentFsEffect(void)
{
    return *(int *)&D_001303E0;
}

static void func_0000DFF8(void)
{
    char *s = (char *)DldSysUndefSymbol != SH_FsEffectDEFAULT ? SH_FsEffectDEFAULT : 0;

    if (s != 0) {
        fsEffectRequestReset(FsEffect_RESET);
    }
}

static void func_0000E058(FsEffect *effect)
{
    for (;;) {
        selectEffect(effect);
        isysSleepSubThread();
    }
}

static void T_0000E0B0(EffectStart *start)
{
    EffectStart params = *start;
    iosFree((int)start);
    for (;;) {
        if (*params.playMode != 1)
            selectEffect(params.effect);
        isysSleepSubThread();
    }
}
