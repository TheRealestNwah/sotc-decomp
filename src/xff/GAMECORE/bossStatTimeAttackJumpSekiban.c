extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern int B_00183E0C;
extern int gstatKaisouMode;
extern int D_00179F90;
extern char *D_00179F94;
extern int ScrIntrDef_JUMP_SEKIBAN;
extern void func_000101D0(void);
extern int _gameWorkChk(int);
extern void setPlayerMaxHp(float);
extern void setPlayerMaxGrip(float);
extern void scriptIntrSignal(int);

typedef struct {
    char pad[0xEC];
} BossStatus;

static inline char *getBossStatus(void)
{
    int w = _gameWorkChk(8);

    if (w == D_00179F90)
        return D_00179F94;
    D_00179F90 = w;
    if (w == -1) {
        D_00179F94 = 0;
        return 0;
    }
    {
        int *sh = DldSysUndefSymbol == SH_BossStatusDEFAULT ? 0 : SH_BossStatusDEFAULT;

        D_00179F94 = (char *)((BossStatus *)sh[4] + w);
    }
    return D_00179F94;
}

void bossStatTimeAttackJumpSekiban(int n)
{
    B_00183E0C = n;
    func_000101D0();
    if (gstatKaisouMode == 0) {
        char *s = getBossStatus();

        setPlayerMaxHp(*(float *)(s + 0xBC));
        setPlayerMaxGrip(*(float *)(s + 0xC0));
    }
    scriptIntrSignal(ScrIntrDef_JUMP_SEKIBAN);
}
