extern float GAMEUTIL_get_cos_ratio(float, float, float, float);

float CAM_get_interp_ratio_by_time(int mode, float a, float b, float t, float bias)
{
    float r = 1.0f;

    if (0.0f < t)
        r = GAMEUTIL_get_cos_ratio(a, b, 0.0f, t);
    if (mode == 0)
        r = 1.0f - r;
    if (0.0f < bias)
        r = r * (1.0f - bias) + bias;
    return r;
}
