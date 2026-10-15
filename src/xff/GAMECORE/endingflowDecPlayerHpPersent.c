extern float getPlayerHp(void);
extern void setPlayerHp(float hp);

void endingflowDecPlayerHpPersent(float ratio)
{
    setPlayerHp(getPlayerHp() * ratio);
}
