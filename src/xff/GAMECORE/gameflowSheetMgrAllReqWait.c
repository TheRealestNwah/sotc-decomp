extern void scrRun(void);
extern void sheetMgrAllReqWait(int *);

void gameflowSheetMgrAllReqWait(void)
{
    int st;
    scrRun();
    sheetMgrAllReqWait(&st);
    while ((unsigned int)(st - 0xDEAF) >= 2)
        scrRun();
}
