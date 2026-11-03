extern float func_00007948(float);
extern float GAMEUTIL_increase_yaw_limit_extend(float yaw, float delta, float upper, float lower,
    int *moved, int upperEnabled, int lowerEnabled, int option);

static inline int isNearlyZero(float value, float tolerance)
{
    if (value < 0.0f) {
        if (-value <= tolerance) {
            goto nearZero;
        } else {
            goto notNearZero;
        }
    } else {
        if (value <= tolerance) {
            goto nearZero;
        } else {
            goto notNearZero;
        }
    }

nearZero:
    return 1;
notNearZero:
    return 0;
}

void GAMEUTIL_increase_yaw_region(float yaw, float delta, float center, float width, int *moved, int option)
{
    float half = width * 0.5f;
    float neg;
    float upper = center;

    if (!isNearlyZero(half, 0.0001f)) {
        upper = func_00007948(center + half);
    }
    width = center;
    neg = -half;
    if (!isNearlyZero(neg, 0.0001f)) {
        width = func_00007948(center + neg);
    }
    GAMEUTIL_increase_yaw_limit_extend(yaw, delta, upper, width, 0, 1, 1, option);
    moved = 0;
}
