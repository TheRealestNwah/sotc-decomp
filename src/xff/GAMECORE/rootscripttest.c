extern int D_0017AF70;
extern void *isysGetThisSubThread(void);
extern char *bossStatGetActiveBoss(void);
extern int bossStatBootChk(void);
extern char *gStatGetGObjAdrs(int);
extern void scrRun(void);

void rootscripttest(void)
{
    char *b;
    isysGetThisSubThread();
    for (;;) {
        b = bossStatGetActiveBoss();
        if (b != 0 && D_0017AF70 != 0 && bossStatBootChk() >= 0 && *(int *)(gStatGetGObjAdrs(*(int *)(b + 0xE8)) + 8) != 0)
            D_0017AF70 = 0;
        scrRun();
    }
}
