#define CLAMP(x, lo, hi) ((x) > (hi) ? (hi) : (x) < (lo) ? (lo) : (x))
extern float _gameFWorkChk(int);
extern float B_00188600;
extern void setgrip(float);

void setPlayerGrip(float g)
{
    g = CLAMP(g, 0.0f, _gameFWorkChk(12));
    B_00188600 = g;
    setgrip(g / _gameFWorkChk(12));
}
