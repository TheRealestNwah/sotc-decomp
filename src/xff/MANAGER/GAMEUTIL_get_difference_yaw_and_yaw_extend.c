extern int GAMEUTIL_is_between_yaw_and_yaw(float, float, float);

static inline float diff_yaw(float a, float b)
{
    float d = b - a;
    if (d < 0.0f)
        d = -d;
    if (3.14159255f < d)
        d = 6.2831851f - d;
    return d;
}

float GAMEUTIL_get_difference_yaw_and_yaw_extend(int *inner, int mode, float a, float b, float c)
{
    int ok = 1;
    float d = diff_yaw(a, b);

    if (mode == 1 && !GAMEUTIL_is_between_yaw_and_yaw(c, a, b)) {
        float d1 = diff_yaw(a, c);
        float d2 = diff_yaw(b, c);
        if (d2 < d1)
            d1 = d2;
        if (3.14159255f < d + d1) {
            ok = 0;
            d = 6.2831851f - d;
        }
    }
    if (inner != 0)
        *inner = ok;
    return d;
}
