typedef struct { char d[20]; } StageData;
typedef struct { char pad[0x10]; StageData *list; } StageDataList;
extern int DldSysUndefSymbol;
extern StageDataList SH_StageDataDEFAULT;

StageData *gcGetStageData(int i)
{
    StageDataList *l = DldSysUndefSymbol == (int)&SH_StageDataDEFAULT ? 0 : &SH_StageDataDEFAULT;
    if (l != 0)
        return &l->list[i];
    return 0;
}
