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

float GAMEUTIL_get_new_velocity(float vel, float min, float accel, float max, float dt)
{
    float v = min;
    float d = vel - min;

    if (d >= 0.0f || is_nearly_zero(d, 0.01f) == 1) {
        v = vel + accel * dt;
    }
    if (max < v) {
        v = max;
    }
    return v;
}
