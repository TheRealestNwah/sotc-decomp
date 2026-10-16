extern unsigned char B_001848B0[];
extern char gcGlobalVar[];
extern void gameFlagCheckPointLoad(void *, void *, void *, void *, void *, void *);
extern void backStageCheckPointLoad(void *);
extern void *getSprLogWorkAddress(void);
extern int getSprLogWorkSize(void);
extern void *getSprLogStatusAddress(void);
extern int getSprLogStatusSize(void);
extern void *memcpy(void *, const void *, unsigned int);
extern int _gameFlagChk(int);
extern void *SCRGetFirstObj(void *);
extern void gStatUnloadHorseChara(void);
extern void gameflowSetJumpSekiban(int);
extern int getGameHardMode(void);
extern void SetDamageClassDamageTableType(int);

int gStatCheckPointLoad(void)
{
    unsigned char *b = B_001848B0;
    unsigned char *work = b + 0xC10;
    unsigned char *status = b + 0x3C10;

    gameFlagCheckPointLoad(b, b + 0x64, b + 0x1F4, b + 0x384, b + 0x6A4, b + 0x3C20);
    backStageCheckPointLoad(b + 0x9C4);
    {
        void *w = getSprLogWorkAddress();

        memcpy(w, work, getSprLogWorkSize());
    }
    {
        void *st = getSprLogStatusAddress();

        memcpy(st, status, getSprLogStatusSize());
    }
    if (_gameFlagChk(0x1C)) {
        if (SCRGetFirstObj(gcGlobalVar + 0x2B4) != 0)
            gStatUnloadHorseChara();
    } else if (_gameFlagChk(0x1E)) {
        gameflowSetJumpSekiban(1);
    }
    SetDamageClassDamageTableType(getGameHardMode());
    return B_001848B0[0x3C1C];
}
