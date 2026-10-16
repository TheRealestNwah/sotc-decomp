extern float B_00188604;
extern float _gameFWorkChk(int);
extern float gStatGetPlayerAccessoriesDamgeRaitoToPlayer(void);
extern float getPlayerHp(void);
extern float getPlayerMaxHp(void);
extern void playerlifebar_sethp(float);

void addPlayerHp(float add)
{
    float v;
    float r;

    if (add < 0.0f)
        add *= gStatGetPlayerAccessoriesDamgeRaitoToPlayer();
    v = B_00188604 + add;
    if (_gameFWorkChk(11) < v)
        r = _gameFWorkChk(11);
    else if (v < 0.0f)
        r = 0.0f;
    else
        r = v;
    B_00188604 = r;
    playerlifebar_sethp(getPlayerHp() / getPlayerMaxHp());
}
