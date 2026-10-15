extern void scrRun(void);
extern void sheetMgrSpecialFsEnd(int, int *);

void gameflowSheetMgrSplFsEnd(int a)
{
    int st;
    scrRun();
    sheetMgrSpecialFsEnd(a, &st);
    while ((unsigned int)(st - 0xDEAF) >= 2)
        scrRun();
}
