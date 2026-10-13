extern float getPlayerHp();
extern float getPlayerMaxHp();

float _getPlayerHpRatio(void)
{
    float temp_f20;

    temp_f20 = getPlayerHp();
    return temp_f20 / getPlayerMaxHp();
}
