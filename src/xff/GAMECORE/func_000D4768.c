extern char SH_StageDataDEFAULT[];
extern int sheetMgrUnloadSegmentIndex();

static int func_000D4768(int a, int b, int c, int d)
{
    return sheetMgrUnloadSegmentIndex((int)SH_StageDataDEFAULT, a, 0, d);
}
