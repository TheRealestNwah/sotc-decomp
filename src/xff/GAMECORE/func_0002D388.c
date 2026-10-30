extern int DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern int sheetMgrUnloadSegmentIndex();
extern void scrRun(void);

static void func_0002D388(int id)
{
    int idx = (id >> 15) & 0x3FFF;
    int status;
    char *t = SH_StageDataDEFAULT == (char *)DldSysUndefSymbol ? 0 : SH_StageDataDEFAULT;
    char *e = t != 0 ? *(char **)(t + 0x10) + idx * 20 : 0;

    if (--*(unsigned short *)(e + 0x10) == 0) {
        sheetMgrUnloadSegmentIndex((int)SH_StageDataDEFAULT, idx, &status);
        while ((unsigned int)(status - 0xDEAF) >= 2)
            scrRun();
    }
}
