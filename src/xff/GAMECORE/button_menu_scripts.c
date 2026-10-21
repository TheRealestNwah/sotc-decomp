extern int isysGetThisSubThread(void);
extern void scrInit(int);
extern void bgmStop(void *, int *, float);
extern void bgmPlay(void *, float);
extern int spriteMenuObjPadChangeHorse(void);
extern void *buttonBgm, *buttonBgmPlay;
extern int B_001885F0, B_001885F4;
static void func_0001D928(void)
{
    bgmStop(buttonBgmPlay, 0, 100.0f);
}
static void T_0001D950(void)
{
    scrInit(isysGetThisSubThread());
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
    scrInit(isysGetThisSubThread());
    B_001885F0 = 2;
}