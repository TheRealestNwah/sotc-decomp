#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
static inline int is_nearly_equal_zero(float value, float tolerance)
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

float GAMEUTIL_increase_pitch(int *moved, int option, float pitch, float delta, float upper, float lower)
{
    int flag = 0;
    float r = pitch;

    if (!is_nearly_equal_zero(delta, 0.0001f)) {
        if (upper > 1.48352981f)
            upper = 1.48352981f;
        else if (lower < -1.48352981f)
            lower = -1.48352981f;
        if (upper < pitch) {
            if (delta < 0.0f) {
                r = pitch + delta;
                flag = 1;
                if (r < upper) {
                    if (option)
                        r = upper;
                }
            }
        } else if (pitch < lower) {
            if (0.0f < delta) {
                r = pitch + delta;
                flag = 1;
                if (lower < r) {
                    if (option)
                        r = lower;
                }
            }
        } else {
            r = pitch + delta;
            flag = 1;
            if (upper < r)
                r = upper;
            else if (r < lower)
                r = lower;
        }
    }
    if (moved)
        *moved = flag;
    return r;
}
#endif
