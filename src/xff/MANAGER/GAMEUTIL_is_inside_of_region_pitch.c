static inline int is_near_zero(float x, float eps)
{
    if (x < 0.0f) {
        if (-x <= eps)
            goto nearZero;
        else
            goto notNearZero;
    } else {
        if (x <= eps)
            goto nearZero;
        else
            goto notNearZero;
    }
nearZero:
    return 1;
notNearZero:
    return 0;
}

static inline float inc_pitch(float pitch, float add, float max, float min)
{
    float out = pitch;
    if (is_near_zero(add, 0.0001f) == 0) {
        if (max > 1.4835299f) {
            max = 1.4835299f;
        } else if (min < -1.4835299f) {
            min = -1.4835299f;
        }
        if (max < pitch) {
            if (add < 0.0f)
                out = pitch + add;
        } else if (pitch < min) {
            if (add > 0.0f)
                out = pitch + add;
        } else {
            out = pitch + add;
            if (max < out)
                out = max;
            else if (out < min)
                out = min;
        }
    }
    return out;
}

int GAMEUTIL_is_inside_of_region_pitch(float *lo, float *hi, float pitch, float center, float range)
{
    float h = range * 0.5f;
    float a = inc_pitch(center, h, 1.4835299f, -1.4835299f);
    float b = inc_pitch(center, -h, 1.4835299f, -1.4835299f);
    if (lo != 0)
        *lo = a;
    if (hi != 0)
        *hi = b;
    if ((a <= pitch && pitch <= b) || (b <= pitch && pitch <= a))
        return 1;
    return 0;
}
