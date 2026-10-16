extern int SH_HorseTypeDEFAULT[];
extern char rootPtn[];
extern int D_0017A294;
extern int _omakeSelectFlagChk(int);
extern void stagemanager_unloadstagecore(int);
extern void stagemanager_loadstagecore(void *, int, int, int);

typedef struct {
    int stage;
    int flag;
    char pad8[0xC];
} HorseType;

static inline HorseType *getHorseType(void)
{
    HorseType *base = (HorseType *)SH_HorseTypeDEFAULT[4];
    int n = SH_HorseTypeDEFAULT[3];
    HorseType *e = base + 1;
    int i;

    n--;
    for (i = 0; i < n; i++, e++) {
        if (_omakeSelectFlagChk(e->flag))
            return e;
    }
    return base;
}

void gStatLoadHorseChara(int arg)
{
    int stage = getHorseType()->stage;

    if (D_0017A294 != 0) {
        if (stage == D_0017A294)
            goto done;
        stagemanager_unloadstagecore(D_0017A294);
    }
    if (stage != 0)
        stagemanager_loadstagecore(rootPtn, stage, arg, 0);
done:
    D_0017A294 = getHorseType()->stage;
}
