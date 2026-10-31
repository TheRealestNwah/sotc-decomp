extern char *SCRGetBossWork(void *);
extern int ScrIntrDef_DEAD_BOSS;
extern void scriptIntrSignal(int);

static void func_00036190(void *boss)
{
    *(int *)(SCRGetBossWork(boss) + 0x44) = 0;
    *(int *)(SCRGetBossWork(boss) + 0xEC) = 1;
    scriptIntrSignal(ScrIntrDef_DEAD_BOSS);
}
