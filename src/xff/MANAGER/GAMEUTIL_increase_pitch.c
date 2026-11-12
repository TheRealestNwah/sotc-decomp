#ifdef NONMATCHING /* 7 diffs (was 28; the unclamped path is two independent ifs, not else-if, and the near-zero check uses the goto nearlyZero idiom from GAMEUTIL_act_pitch_rot_limit_clip): the clamp-to-limit tails use bnel instead of beqz + b, and the max clamp branches past the min check */
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
float GAMEUTIL_increase_pitch(int *changed, int clamp, float pitch, float add, float max, float min)
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
#endif
