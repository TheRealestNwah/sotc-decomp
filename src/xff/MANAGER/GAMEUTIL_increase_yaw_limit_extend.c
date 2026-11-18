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

static inline float increaseYaw(int *moved, float yaw, float delta)
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

extern int GAMEUTIL_is_between_yaw_and_yaw(float, float, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern int GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(float *, float, float, float);

float GAMEUTIL_increase_yaw_limit_extend(int *moved, int upperEnabled, int lowerEnabled,
    int option, float yaw, float delta, float upper, float lower)
{
    int m = 0;
    float next = increaseYaw(&m, yaw, delta);
    float result = next;
    float d;
    int enabled;
    int dir;

    if (m == 1) {
        if (GAMEUTIL_is_between_yaw_and_yaw(yaw, upper, lower) == 1) {
            if (!GAMEUTIL_is_between_yaw_and_yaw(next, upper, lower)) {
                d = GAMEUTIL_get_difference_yaw_and_yaw(next, upper);
                if (d <= GAMEUTIL_get_difference_yaw_and_yaw(next, lower)) {
                    if (upperEnabled == 1)
                        result = upper;
                } else if (lowerEnabled == 1) {
                    result = lower;
                }
            }
        } else {
            d = GAMEUTIL_get_difference_yaw_and_yaw(yaw, upper);
            enabled = upperEnabled;
            if (GAMEUTIL_get_difference_yaw_and_yaw(yaw, lower) < d) {
                enabled = lowerEnabled;
                upper = lower;
            }
            if (enabled == 1) {
                dir = GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(0, yaw, 1.0f, upper);
                if ((dir == 1 && delta < 0.0f) || (dir == -1 && 0.0f < delta)) {
                    result = yaw;
                    m = 0;
                } else if (option == 1) {
                    if (GAMEUTIL_is_between_yaw_and_yaw(upper, yaw, next) == option)
                        result = upper;
                }
            }
        }
    }
    if (moved != 0)
        *moved = m;
    return result;
}
