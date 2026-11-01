extern int gstatTimeAttackMode;
extern char B_001848B0[];
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);
extern int getHorseStandByMode(void);
extern void gameFlagCheckPointSave(void *, void *, void *, void *, void *, void *);
extern void backStageCheckPointSave(void *);
extern void *getSprLogWorkAddress(void);
extern int getSprLogWorkSize(void);
extern void *getSprLogStatusAddress(void);
extern int getSprLogStatusSize(void);
extern void *memcpy(void *, const void *, unsigned int);

static void func_00018E00(int var, int flag)
{
    char *b;

    if (gstatTimeAttackMode != 0)
        return;
    if (flag == 0)
        _gameFlagSet(0x1C);
    else
        _gameFlagCls(0x1C);
    if (getHorseStandByMode())
        _gameFlagSet(0x1E);
    else
        _gameFlagCls(0x1E);
    b = B_001848B0;
    gameFlagCheckPointSave(b, b + 0x64, b + 0x1F4, b + 0x384, b + 0x6A4, b + 0x3C20);
    backStageCheckPointSave(b + 0x9C4);
    {
    char *d1 = b + 0xC10;
    void *s1 = getSprLogWorkAddress();
    memcpy(d1, s1, getSprLogWorkSize());
    }
    {
    char *d2 = b + 0x3C10;
    void *s2 = getSprLogStatusAddress();
    memcpy(d2, s2, getSprLogStatusSize());
    }
    b[0x3C1C] = var;
}
