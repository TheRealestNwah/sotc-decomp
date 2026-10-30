extern int DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern char rootPtn[];
extern int sheetMgrLoadSegmentIndex();
extern void sheetMgrNopSegmentIndex(int);
extern void scrRun(void);
extern int initstage();

static void func_0002D090(int idx)
{
    char *ptn = rootPtn;
    int status;
    char *t = SH_StageDataDEFAULT != (char *)DldSysUndefSymbol ? SH_StageDataDEFAULT : 0;
    char *e = t != 0 ? *(char **)(t + 0x10) + idx * 20 : 0;

    if (++*(unsigned short *)(e + 0x10) == 1) {
        sheetMgrLoadSegmentIndex((int)SH_StageDataDEFAULT, idx, &status);
        sheetMgrNopSegmentIndex(0);
        while ((unsigned int)(status - 0xDEAF) >= 2)
            scrRun();
        if (status != 0xDEB0)
            initstage(ptn, idx, -1, -1, 1, 0);
    }
}
