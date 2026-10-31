extern void setFullPower(void);
extern float getPlayerMaxHp(void);
extern void setPlayerHp(float);

static void T_0007D9B0(void)
{
    setFullPower();
    setPlayerHp(getPlayerMaxHp());
}
