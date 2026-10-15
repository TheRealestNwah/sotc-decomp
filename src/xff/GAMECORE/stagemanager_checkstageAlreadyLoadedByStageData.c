typedef struct { int a[5]; } Stage;
extern int DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern int sheetMgrChkStageIndexResolve(int);

int stagemanager_checkstageAlreadyLoadedByStageData(Stage *s)
{
    char *d = (char *)DldSysUndefSymbol == SH_StageDataDEFAULT ? 0 : SH_StageDataDEFAULT;
    Stage *base = d != 0 ? *(Stage **)(d + 0x10) : 0;
    int r = sheetMgrChkStageIndexResolve(s - base);
    s = 0;
    return r;
}
