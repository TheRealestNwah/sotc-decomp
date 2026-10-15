#define CLAMP(x, lo, hi) ((x) > (hi) ? (hi) : (x) < (lo) ? (lo) : (x))
extern float _gameFWorkChk(int);
extern float B_00188604;
extern float getPlayerHp(void);
extern float getPlayerMaxHp(void);
extern void playerlifebar_sethp(float);

void setPlayerHp(float hp)
{
    hp = CLAMP(hp, 0.0f, _gameFWorkChk(11));
    B_00188604 = hp;
    playerlifebar_sethp(getPlayerHp() / getPlayerMaxHp());
}
