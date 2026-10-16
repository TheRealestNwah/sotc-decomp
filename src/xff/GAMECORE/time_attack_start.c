extern int gstatKaisouMode;
extern int gstatTimeAttackMode;
extern int B_001887B8;
extern int B_001887BC;
extern float getPlayerMaxHp(void);
extern float getPlayerMaxGrip(void);
extern void gStatCheckPointSave(void);
extern void gStatInitNotOmakeInit(void);
extern int gstatBootMcChkExistIcoData(void);
extern int getGameHardMode(void);
extern void omakeStatInit(int, int, int);
extern void setPlayerMaxHp(float);
extern void setPlayerMaxGrip(float);
extern void setSmallManagerSystemLock(int);
extern void bossStatTimeAttackJumpSekiban(int);

void time_attack_start(void)
{
    float hp = getPlayerMaxHp();
    float grip = getPlayerMaxGrip();

    gStatCheckPointSave();
    gstatTimeAttackMode = 1;
    gstatKaisouMode = B_001887BC;
    gStatInitNotOmakeInit();
    if (gstatKaisouMode == 0) {
        int e = gstatBootMcChkExistIcoData();

        omakeStatInit(e, 0, getGameHardMode());
    } else {
        setPlayerMaxHp(hp);
        setPlayerMaxGrip(grip);
    }
    setSmallManagerSystemLock(1);
    bossStatTimeAttackJumpSekiban(B_001887B8);
}
