extern char SH_StageDataDEFAULT[];
extern int sheetMgrLoadSegmentIndex();

int stagemanager_loadstage_nowait_norefcount(int a, int b, int c, int d)
{
    return sheetMgrLoadSegmentIndex((int)SH_StageDataDEFAULT, a, 0, d);
}
