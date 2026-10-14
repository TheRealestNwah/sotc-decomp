extern float getPlayerHp();
extern float getPlayerMaxHp();

float getPlayerHpRatio(void) {
    float temp_f20;

    temp_f20 = getPlayerHp();
    return (temp_f20 / getPlayerMaxHp()) * 100.0f;
}
