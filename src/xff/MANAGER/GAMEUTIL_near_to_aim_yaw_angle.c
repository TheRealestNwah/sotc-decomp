extern int GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(float *, float, float, float);

static inline int is_near_zero(float x, float eps)
{
    if ((x < 0.0f ? -x : x) <= eps) {
        return 1;
    }
    return 0;
}

static inline int is_reach(float *out, float a, float b, float aim)
{
    float d = a - b;
    int wrap = 0;
    int r;

    if (d < 0.0f ? d < -3.14159255f : d > 3.14159255f) {
        wrap = 1;
    }
    if ((a <= aim && aim <= b) || (b <= aim && aim <= a)) {
        r = wrap == 0;
    } else {
        r = wrap != 0;
    }
    if (r == 1) {
        goto hit;
    }
    d = aim - b;
    if (d < 0.0f) {
        d = -d;
    }
    if (d > 3.14159255f) {
        d = 6.2831851f - d;
    }
    r = is_near_zero(d, 0.0001f);
    if (r == 1) {
    hit:
        if (out != 0) {
            *out = aim;
        }
        return 1;
    }
    if (out != 0) {
        *out = b;
    }
    return 0;
}

int GAMEUTIL_near_to_aim_yaw_angle(float *cur, int *dir, float from, float step, float aim)
{
    int d = GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(cur, from, step, aim);

    if (dir != 0) {
        *dir = d;
    }
    return is_reach(cur, from, *cur, aim);
}
