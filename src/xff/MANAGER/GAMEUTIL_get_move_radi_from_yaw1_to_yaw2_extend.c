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

static inline float diffExtend(int *inner, int mode, float a, float b, float c)
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

static inline float moveRadi(float a, float b)
{
    float d = b - a;
    int pos;
    if (d < 0.0f)
        d = -d;
    pos = 1;
    if (b < a)
        pos = 0;
    if (3.1415926f < d) {
        pos = !pos;
        d = 6.2831852f - d;
    }
    if (pos)
        return d;
    return -d;
}

float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2_extend(int *inner, int mode, float a, float b, float c)
{
    int ok = 1;
    float move = moveRadi(a, b);

    if (mode == 1) {
        float d = diffExtend(&ok, mode, a, b, c);

        if (!ok) {
            if (0.0f <= move)
                move = -d;
            else
                move = d;
        }
    }
    if (inner != 0)
        *inner = ok;
    return move;
}
