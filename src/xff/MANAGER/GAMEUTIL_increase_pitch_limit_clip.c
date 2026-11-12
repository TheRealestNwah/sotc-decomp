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
static inline float increase_pitch(int *changed, int clamp, float pitch, float add, float max, float min)
{
    int r;
    float out;
    r = 0;
    out = pitch;
    if (is_near_zero(add, 0.0001f) == 0) {
        if (max > 1.4835299f) {
            max = 1.4835299f;
        } else if (min < -1.4835299f) {
            min = -1.4835299f;
        }
        if (max < pitch) {
            if (add < 0.0f) {
                out = pitch + add;
                r = 1;
                if (out < max && clamp != 0) {
                    out = max;
                }
            }
        } else if (pitch < min) {
            if (add > 0.0f) {
                out = pitch + add;
                r = 1;
                if (min < out && clamp != 0) {
                    out = min;
                }
            }
        } else {
            out = pitch + add;
            if (max < out) {
                out = max;
            }
            if (out < min) {
                out = min;
            }
            r = 1;
        }
    }
    if (changed != 0) {
        *changed = r;
    }
    return out;
}

#ifdef NONMATCHING
/* 7 diffs (was 43, same fixes as GAMEUTIL_increase_pitch: goto nearlyZero idiom, two independent ifs on the unclamped path): the inlined copy keeps the same clamp-tail bnel shapes as the standalone one */
float GAMEUTIL_increase_pitch_limit_clip(int *changed, int clamp, float pitch, float add, float max, float min)
{
    int r;
    float out;
    r = 0;
    out = increase_pitch(&r, clamp, pitch, add, max, min);
    if (max < out) {
        out = max;
        r = 1;
    } else if (out < min) {
        out = min;
        r = 1;
    }
    if (changed != 0) {
        *changed = r;
    }
    return out;
}
#endif
