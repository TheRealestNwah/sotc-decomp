static inline int is_near_zero(float x, float eps)
{
    if ((x < 0.0f ? -x : x) <= eps) {
        return 1;
    }
    return 0;
}

static inline float add_pitch_limit(float cur, float add, float max, float min)
{
    float res = cur;

    if (is_near_zero(add, 0.0001f)) {
        return res;
    }
    if (max > 1.48352981f) {
        max = 1.48352981f;
    } else if (min < -1.48352981f) {
        min = -1.48352981f;
    }
    if (max < cur) {
        if (add < 0.0f) {
            res = cur + add;
        }
    } else if (cur < min) {
        if (add > 0.0f) {
            res = cur + add;
        }
    } else {
        res = cur + add;
        if (max < res) {
            res = max;
        } else if (res < min) {
            res = min;
        }
    }
    return res;
}

float GAMEUTIL_get_interp_pitch(float from, float to, float t)
{
    if (t <= 0.0f) {
        return from;
    }
    if (1.0f <= t) {
        return to;
    }
    return add_pitch_limit(from, t * (to - from), 1.48352981f, -1.48352981f);
}
