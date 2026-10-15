extern void scrRun(void);
extern char SH_StageDataDEFAULT[];
extern void sheetMgrLoadSegmentIndex(void *, int, int *);

void languageMenuLoad(void)
{
    int st;
    sheetMgrLoadSegmentIndex(SH_StageDataDEFAULT, 0x760, &st);
    while ((unsigned int)(st - 0xDEAF) >= 2)
        scrRun();
}
