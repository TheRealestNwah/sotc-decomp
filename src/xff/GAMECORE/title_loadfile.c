extern int spriteMenuObjPadChangeHorse(void);
extern int checkPointChangeHorse;
extern int D_0017B278;
extern void func_000C9C30();
extern int opflowCompareOptionData();
extern void bootMemoryCardLoadScriptNoBlock(void *, void *);

void title_loadfile(void)
{
    checkPointChangeHorse = spriteMenuObjPadChangeHorse();
    D_0017B278 = 1;
    bootMemoryCardLoadScriptNoBlock(func_000C9C30, opflowCompareOptionData);
}
