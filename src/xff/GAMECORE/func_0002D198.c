extern int DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern int sheetMgrUnloadSegmentIndex();
extern void scrRun(void);

static void func_0002D198(int idx)
{
    int status;
    char *t = SH_StageDataDEFAULT != (char *)DldSysUndefSymbol ? SH_StageDataDEFAULT : 0;
    char *e = t != 0 ? *(char **)(t + 0x10) + idx * 20 : 0;

    if (--*(unsigned short *)(e + 0x10) == 0) {
        sheetMgrUnloadSegmentIndex((int)SH_StageDataDEFAULT, idx, &status);
        while ((unsigned int)(status - 0xDEAF) >= 2)
            scrRun();
    }
}
