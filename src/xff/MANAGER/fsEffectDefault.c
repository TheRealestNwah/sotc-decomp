typedef struct {
    int f0;
    int prio : 28;
    int pad : 4;
} FsEffect;

extern int DldSysUndefSymbol;
extern char SH_FsEffectDEFAULT[];
extern FsEffect B_00147310;
extern FsEffect *D_001303E0;

static inline void fsEffectRequest(FsEffect *effect)
{
    if (effect != 0) {
        if (D_001303E0 == 0) {
            D_001303E0 = effect;
        } else if (effect->prio >= D_001303E0->prio) {
            D_001303E0 = effect;
        }
    }
}

void fsEffectDefault(void)
{
    char *s = (char *)DldSysUndefSymbol != SH_FsEffectDEFAULT ? SH_FsEffectDEFAULT : 0;

    if (s != 0) {
        fsEffectRequest(&B_00147310);
    }
}
