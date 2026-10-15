extern void scrRun(void);
extern void sheetMgrSpecialFsStart(int, int, int *);

void gameflowSheetMgrSplFsStart(int a)
{
    int st;
    scrRun();
    sheetMgrSpecialFsStart(a, 1, &st);
    while ((unsigned int)(st - 0xDEAF) >= 2)
        scrRun();
}
