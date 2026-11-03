#ifdef NONMATCHING /* 30 instruction diffs: the near-zero check and the clamp-to-limit branches come out with inverted branch-likely shapes */
static inline int is_near_zero(float x, float eps)
{
    if (x < 0.0f) {
        if (-x > eps) {
            return 0;
        }
        return 1;
    }
    if (x > eps) {
        return 0;
    }
    return 1;
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
            } else if (out < min) {
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
