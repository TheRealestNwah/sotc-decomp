extern float getPlayerHp(void);
extern float getPlayerMaxHp(void);
extern float D_0017A00C;

void endingflowSetTimePlayerHpMax(float time)
{
    float max = getPlayerMaxHp();
    float diff = max - getPlayerHp();

    D_0017A00C = diff / time;
}
