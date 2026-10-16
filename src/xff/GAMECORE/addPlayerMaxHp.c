extern float _gameFWorkChk(int);
extern void _gameFWorkSet(int, float);
extern void playerlifebar_effect(int);

void addPlayerMaxHp(float add)
{
    int old = _gameFWorkChk(11);
    float v = _gameFWorkChk(11) + add;
    float r;

    if (v > 570.0f)
        r = 570.0f;
    else
        r = v;
    _gameFWorkSet(11, r);
    if (_gameFWorkChk(11) > old)
        playerlifebar_effect(1);
}
