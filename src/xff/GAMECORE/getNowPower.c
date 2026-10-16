extern float B_00188608;
extern float _gameFWorkChk(int);

float getNowPower(void)
{
    float r = _gameFWorkChk(12) / 100.0f;

    return B_00188608 * r;
}
