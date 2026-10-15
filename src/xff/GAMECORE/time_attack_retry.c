extern int gstatKaisouMode;
extern int B_001887B8;
extern float getPlayerMaxHp(void);
extern float getPlayerMaxGrip(void);
extern void gStatInitNotOmakeInit(void);
extern void omakeGetAndSelectCls(int);
extern void setPlayerMaxHp(float);
extern void setPlayerMaxGrip(float);
extern void bossStatTimeAttackJumpSekiban(int);

void time_attack_retry(void)
{
    float hp = getPlayerMaxHp();
    float grip = getPlayerMaxGrip();
    gStatInitNotOmakeInit();
    omakeGetAndSelectCls(16);
    if (gstatKaisouMode != 0) {
        setPlayerMaxHp(hp);
        setPlayerMaxGrip(grip);
    }
    bossStatTimeAttackJumpSekiban(B_001887B8);
}
