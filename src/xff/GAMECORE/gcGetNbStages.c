typedef struct {
    char pad0[0xC];
    int nbStages;
} StageData;
extern StageData SH_StageDataDEFAULT;
extern void *DldSysUndefSymbol;

int gcGetNbStages(void)
{
    StageData *s = DldSysUndefSymbol == &SH_StageDataDEFAULT ? 0 : &SH_StageDataDEFAULT;

    if (s) {
        return s->nbStages;
    }
    return 0;
}
