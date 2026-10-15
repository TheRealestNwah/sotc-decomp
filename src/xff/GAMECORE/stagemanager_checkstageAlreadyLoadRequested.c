typedef struct { char pad[0x10]; unsigned short loaded; char pad2[2]; } StageData;
typedef struct { char pad[0x10]; StageData *list; } StageDataList;
extern int DldSysUndefSymbol;
extern StageDataList SH_StageDataDEFAULT;

int stagemanager_checkstageAlreadyLoadRequested(int i)
{
    StageDataList *l = DldSysUndefSymbol == (int)&SH_StageDataDEFAULT ? 0 : &SH_StageDataDEFAULT;
    StageData *s = l != 0 ? &l->list[i] : 0;
    return s->loaded;
}
