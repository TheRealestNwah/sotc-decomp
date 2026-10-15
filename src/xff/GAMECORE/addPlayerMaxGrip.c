extern float _gameFWorkChk(int);
extern void _gameFWorkSet(int, float);
extern void startGaugeMaxAddEffect(void);

void addPlayerMaxGrip(float add)
{
    float v = _gameFWorkChk(12) + add;
    _gameFWorkSet(12, v > 700.0f ? 700.0f : v < 100.0f ? 100.0f : v);
    if (add > 0.0f)
        startGaugeMaxAddEffect();
}
