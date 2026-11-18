extern float func_00007948(float);
extern float func_000079E8(float);
extern float func_00007A48(float, float, float);

static inline int nearlyZero(float value, float tolerance)
{
    if (value < 0.0f) {
        if (-value <= tolerance)
            goto nearZero;
        else
            goto notNearZero;
    } else {
        if (value <= tolerance)
            goto nearZero;
        else
            goto notNearZero;
    }
nearZero:
    return 1;
notNearZero:
    return 0;
}

static inline float yawDistance(float a, float b)
{
    float d = a - b;

    if (d < 0.0f)
        d = -d;
    if (d > 3.14159251f)
        d = 6.28318501f - d;
    return d;
}

int GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(float *out, float from, float step, float aim)
{
    int dir = 0;
    float result = from;
    float delta;
    float plus;
    float minus;

    if (from != aim) {
        delta = func_000079E8(step);
        plus = from;
        if (nearlyZero(delta, 0.0001f) == 0)
            plus = func_00007948(from + delta);
        minus = from;
        if (nearlyZero(-delta, 0.0001f) == 0)
            { float neg = -delta; minus = func_00007948(from + neg); }
        if (yawDistance(aim, plus) < yawDistance(aim, minus)) {
            result = plus;
            dir = 1;
        } else {
            result = minus;
            dir = -1;
        }
        result = func_00007A48(result, from, step);
    }
    if (out != 0)
        *out = result;
    return dir;
}
