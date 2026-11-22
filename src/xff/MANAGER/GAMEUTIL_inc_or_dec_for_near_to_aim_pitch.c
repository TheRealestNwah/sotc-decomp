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

static inline float increase_pitch(int clamp, float pitch, float add, float max, float min)
{
    float out;
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
                if (out < max && clamp != 0) {
                    out = max;
                }
            }
        } else if (pitch < min) {
            if (add > 0.0f) {
                out = pitch + add;
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
        }
    }
    return out;
}

/* Steps a pitch toward aim by +step or -step (1.0 when step is nearly zero),
 * whichever lands nearer, within [min, max]; returns the direction taken. */
int GAMEUTIL_inc_or_dec_for_near_to_aim_pitch(float *out, int clamp, float from, float step, float aim, float max, float min)
{
    int dir = 0;
    float result = from;
    float add;
    float plus;
    float minus;
    float d1;
    float d2;

    if (from != aim) {
        int zero = is_near_zero(step, 0.0001f);
        add = 1.0f;
        if (zero == 0)
            add = step;
        plus = increase_pitch(clamp, from, add, max, min);
        minus = increase_pitch(clamp, from, -add, max, min);
        d1 = aim - plus;
        if (d1 < 0.0f)
            d1 = -d1;
        d2 = aim - minus;
        if (d2 < 0.0f)
            d2 = -d2;
        if (d1 < d2) {
            result = plus;
            dir = 1;
        } else {
            result = minus;
            dir = -1;
        }
        if (is_near_zero(step, 0.0001f) != 0)
            result = from;
    }
    if (out != 0)
        *out = result;
    return dir;
}
