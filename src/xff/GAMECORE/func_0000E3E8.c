#define DEG2RAD(d) ((d) * 3.14159265358979323846 / 180.0f)

typedef struct {
    char pad0[0xA8];
    float fA8;
    float fAC;
    char padB0[0x120 - 0xB0];
    float f120;
    float f124;
} YawPitchCntrl;

extern float GAMEUTIL_increase_pitch_limit_clip(float, float, float, int, int, float);

static float func_0000E158(YawPitchCntrl *c, float x)
{
    return GAMEUTIL_increase_pitch_limit_clip(c->f120, -c->fA8, DEG2RAD(85.0f), 0, 0, x);
}

static float func_0000E198(float x, YawPitchCntrl *c)
{
    return GAMEUTIL_increase_pitch_limit_clip(c->f124, -c->fAC, x, 0, 0, -DEG2RAD(85.0f));
}

static float func_0000E3E8(YawPitchCntrl *c, float a, float b, float x)
{
    float hi = func_0000E158(c, x);
    float lo = func_0000E198(x, c);

    return GAMEUTIL_increase_pitch_limit_clip(a, b, hi, 0, 0, lo);
}
