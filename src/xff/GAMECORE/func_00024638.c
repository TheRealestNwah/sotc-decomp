extern int D_0017A34C;
extern void sheetMgrStageTexLoad(int, int, int, int *);
extern void isysSleepSubThread(void);
extern void iosFree(void *);

static void func_00024638(int *req)
{
    int st;
    sheetMgrStageTexLoad(D_0017A34C, req[0], req[1], &st);
    while ((unsigned int)(st - 0xDEAF) >= 2)
        isysSleepSubThread();
    iosFree(req);
}
