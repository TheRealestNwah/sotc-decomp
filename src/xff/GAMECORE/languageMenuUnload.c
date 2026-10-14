extern char SH_StageDataDEFAULT[];
extern int sheetMgrUnloadSegmentIndex();

int languageMenuUnload(int a, int b, int c, int d)
{
    return sheetMgrUnloadSegmentIndex((int)SH_StageDataDEFAULT, 1888, 0, d);
}
