extern int D_0017B274;
extern int D_0017B280;
extern int ScrIntrDef_GAME_NEWSTART;
extern void setGameHardMode(int);
extern int scriptIntrSignal(int);

int title_newfile_hard(void)
{
    D_0017B274 = 0;
    D_0017B280 = 0;
    setGameHardMode(1);
    return scriptIntrSignal(ScrIntrDef_GAME_NEWSTART);
}
