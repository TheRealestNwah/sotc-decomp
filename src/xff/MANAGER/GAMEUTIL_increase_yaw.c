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

float GAMEUTIL_increase_yaw(int *moved, float yaw, float delta)
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
