extern int isysGetThisSubThread();
extern void scrInit(int);
extern void scrRun();
extern void scriptIntrAllDeleteJump(int);
extern void scriptIntrEntryJump(int, int, void *);
extern unsigned char D_0017AF80[];
extern int ScrIntrDef_DEAD_BOSS;

void st_boss_status(void)
{
    int temp_v0;

    temp_v0 = isysGetThisSubThread();
    scrInit(temp_v0);
    scriptIntrAllDeleteJump(temp_v0);
    scriptIntrEntryJump(ScrIntrDef_DEAD_BOSS, temp_v0, D_0017AF80);
loop_1:
    scrRun();
    goto loop_1;
}
