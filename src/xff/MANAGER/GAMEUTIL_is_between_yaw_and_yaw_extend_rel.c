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
extern int GAMEUTIL_is_between_yaw_and_yaw_extend_abs(float, float, float, float);

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

int GAMEUTIL_is_between_yaw_and_yaw_extend_rel(float yaw, float base, float extend1, float extend2)
{
    float yaw1 = increase_yaw(0, base, extend1);
    float yaw2 = increase_yaw(0, base, extend2);
    return GAMEUTIL_is_between_yaw_and_yaw_extend_abs(yaw, base, yaw1, yaw2);
}
