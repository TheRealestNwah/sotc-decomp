extern float GAMEUTIL_get_interp_value_interp_value_cntrl(void *);
extern float GAMEUTIL_mul_ratio(int clamp, float a, float r);

static float func_000E2670(void *pos, void *neg, float t)
{
    float r;

    if (t == 0.0f)
        return 0.0f;
    if (0.0f < t)
        r = GAMEUTIL_get_interp_value_interp_value_cntrl(pos);
    else
        r = GAMEUTIL_get_interp_value_interp_value_cntrl(neg);
    return GAMEUTIL_mul_ratio(1, t, r);
}
