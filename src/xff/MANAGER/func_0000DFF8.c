typedef struct {
    int f0;
    int prio : 28;
    int pad : 4;
} FsEffect;

extern int DldSysUndefSymbol;
extern char SH_FsEffectDEFAULT[];
extern FsEffect *FsEffect_RESET;
extern FsEffect *D_001303E0;

static inline void fsEffectRequest(FsEffect *effect)
{
    if (effect != 0) {
        if (D_001303E0 == 0 || !(effect->prio < D_001303E0->prio)) {
            D_001303E0 = effect;
        }
    }
}

static void func_0000DFF8(void)
{
    char *s = (char *)DldSysUndefSymbol != SH_FsEffectDEFAULT ? SH_FsEffectDEFAULT : 0;

    if (s != 0) {
        fsEffectRequest(FsEffect_RESET);
    }
}
