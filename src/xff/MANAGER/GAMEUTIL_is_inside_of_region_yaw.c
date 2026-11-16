static inline int is_nearly_zero(float x, float eps)
{
    if (x < 0.0f) {
        if (-x <= eps) {
            goto yes;
        } else {
            goto no;
        }
    } else {
        if (x <= eps) {
            goto yes;
        } else {
            goto no;
        }
    }
yes:
    return 1;
no:
    return 0;
}

static inline int is_over_pi(float d)
{
    int r = 0;
    if (d < 0.0f) {
        if (d < -3.1415926f)
            goto yes;
        goto no;
    }
    if (3.1415926f < d)
        goto yes;
    goto no;
yes:
    r = 1;
no:
    return r;
}

extern float func_00007948(float);

static inline float increase_yaw(float yaw, float delta)
{
    float y = yaw;

    if (is_nearly_zero(delta, 0.0001f) == 0) {
        y = func_00007948(yaw + delta);
    }
    return y;
}

int GAMEUTIL_is_inside_of_region_yaw(float *lo, float *hi, float yaw, float center, float range)
{
    float h = range * 0.5f;
    float a = increase_yaw(center, h);
    float b = increase_yaw(center, -h);
    float d;
    int wrap;

    if (lo != 0)
        *lo = a;
    if (hi != 0)
        *hi = b;
    d = a - b;
    wrap = is_over_pi(d); __asm__("" : "+r"(wrap));
    if ((a <= yaw && yaw <= b) || (b <= yaw && yaw <= a))
        return wrap == 0;
    return wrap != 0;
}
