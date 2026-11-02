extern void *DldSysUndefSymbol;

typedef struct FsEffectDemo {
    int pad0;
    int priority : 28;
    unsigned int flags : 4;
} FsEffectDemo;

typedef struct FsEffectDemoParam {
    int pad0;
    unsigned int effect;
    unsigned int sub;
} FsEffectDemoParam;

typedef struct FsEffectDemoState {
    FsEffectDemo *effect;
    void *sub;
} FsEffectDemoState;

extern FsEffectDemoState D_001303E0;

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

void fsEffectManagerSetDemoParam(FsEffectDemoParam *param)
{
    FsEffectDemo *effect = resolveSymbolData(&param->effect);
    void *sub = resolveSymbolData(&param->sub);

    if (effect) {
        if (D_001303E0.effect == 0 || effect->priority >= D_001303E0.effect->priority) {
            D_001303E0.effect = effect;
        }
    }
    D_001303E0.sub = sub;
}
