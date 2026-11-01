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

extern float func_00007948(float);

static inline float increase_yaw(int *moved, float yaw, float delta)
{
    int m = 0;
    float y = yaw;

    if (is_nearly_zero(delta, 0.0001f) == 0) {
        y = func_00007948(yaw + delta);
        m = 1;
    }
    if (moved != 0) {
        *moved = m;
    }
    return y;
}

float GAMEUTIL_get_interp_yaw(float from, float to, float t)
{
    float d;
    float diff;
    int pos;

    if (t <= 0.0f) {
        return from;
    }
    if (1.0f <= t) {
        return to;
    }
    d = to - from;
    if (d < 0.0f) {
        d = -d;
    }
    pos = 1;
    if (to < from) {
        pos = 0;
    }
    if (3.1415925026f < d) {
        d = 6.28318501f - d;
        pos = !pos;
    }
    if (pos) {
        diff = d;
    } else {
        diff = -d;
    }
    return increase_yaw(0, from, t * diff);
}
