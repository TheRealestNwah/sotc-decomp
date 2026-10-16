extern float B_00188600;
extern float _gameFWorkChk(int);
extern void setgrip(float);

void addPlayerGrip(float add)
{
    float v = B_00188600 + add;

    v = _gameFWorkChk(12) < v ? _gameFWorkChk(12) : (v < 0.0f ? 0.0f : v);
    B_00188600 = v;
    setgrip(v / _gameFWorkChk(12));
}
