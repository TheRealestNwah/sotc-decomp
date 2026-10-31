extern int D_0017A34C;
extern void sheetMgrStageTexUnload(int, int, int, int *);
extern void isysSleepSubThread(void);
extern void iosFree(void *);

static void T_000246C0(int *p)
{
    int st;

    sheetMgrStageTexUnload(D_0017A34C, p[0], p[1], &st);
    while ((unsigned int)(st - 0xDEAF) >= 2) {
        isysSleepSubThread();
    }
    iosFree(p);
}
