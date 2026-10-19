typedef struct Ptn Ptn;
typedef struct {
    int unknown;
    signed int priority : 28;
    unsigned int flags : 4;
    char rest[88];
} FsEffect;
typedef struct {
    FsEffect *effect;
    const signed char *playMode;
} EffectStart;
extern Ptn rootPtn;
extern void *D_001303E0;
extern void *iosMallocAlign(Ptn *, int, int);
extern void iosFree(int);
extern void isysSleepSubThread(void);
extern void *createScriptObj(void *, int, Ptn *, int, int, int, int, int);
extern void SetScriptObjDeleteCallBackFunc(void *, int, int);
static void func_0000DFF8(void);
static void T_0000E0B0(EffectStart *);
static inline void selectEffect(FsEffect *effect)
{
    if (effect && (!D_001303E0 || effect->priority >= ((FsEffect *)D_001303E0)->priority))
        D_001303E0 = effect;
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
