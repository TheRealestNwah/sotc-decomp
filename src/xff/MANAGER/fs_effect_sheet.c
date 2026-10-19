extern void *DldSysUndefSymbol;
typedef struct Ptn Ptn;
extern Ptn rootPtn;
static void func_0000E058(void);
static void func_0000DFF8(void);
extern void *createScriptObj(void *, int, Ptn *, int, int, int, int, int);
extern void SetScriptObjDeleteCallBackFunc(void *, int, int);
extern void iosLocalPrintf(const char *, ...);
extern const char RO_0013C920[];
typedef struct { int unknown; signed int priority : 28; unsigned int flags : 4; char rest[88]; } FsEffect;
extern void *D_001303E0;
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
void fsEffectSetParamSheetSeg(unsigned int *reference)
{
    FsEffect *effect = (FsEffect *)resourceData(reference);
    if (effect && (!D_001303E0 ||
        effect->priority >= ((FsEffect *)D_001303E0)->priority))
        D_001303E0 = effect;
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
