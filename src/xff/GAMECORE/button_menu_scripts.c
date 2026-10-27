extern void *isysGetThisSubThread(void);
extern void scrInit(int);
extern void bgmStop(void *, int *, float);
extern void bgmPlay(void *, float);
extern int spriteMenuObjPadChangeHorse(void);
extern void *buttonBgm, *buttonBgmPlay;
extern int B_001885F0, B_001885F4;
extern void scriptIntrEntryJump(int, int, void *);
extern void scrRun(void);
extern int ScrIntrDef_GAME_NEWSTART, ScrIntrDef_GAME_LOADSTART;
extern char D_0017A2E8[], D_0017A2F0[];

static void func_0001D928(void)
{
    bgmStop(buttonBgmPlay, 0, 100.0f);
}
static void T_0001D950(void)
{
    scrInit((int)isysGetThisSubThread());
    if (buttonBgm != 0) {
        bgmPlay(buttonBgm, 100.0f);
        buttonBgmPlay = buttonBgm;
        buttonBgm = 0;
    }
    B_001885F0 = 1;
    B_001885F4 = spriteMenuObjPadChangeHorse();
}
static void func_0001D9C8(void)
{
    scrInit((int)isysGetThisSubThread());
    B_001885F0 = 2;
}
static void func_0001D9F8(void)
{
    int thread = (int)isysGetThisSubThread();
    scrInit(thread);
    scriptIntrEntryJump(ScrIntrDef_GAME_NEWSTART, thread, D_0017A2E8);
    scriptIntrEntryJump(ScrIntrDef_GAME_LOADSTART, thread, D_0017A2F0);
    for (;;)
        scrRun();
}