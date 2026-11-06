#ifdef NONMATCHING /* 43 diffs: f1/f2/f12 register assignment of the step and zero constant in the spring clamp */
extern int GAMEUTIL_is_nearly_equal_zero(float value, float tolerance);

float GAMEUTIL_get_spring_damp_offset(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float dt)
{
    float d = a3 - a1;
    float half = a2 * 0.5f;
    float low = -half;
    float result = 0.0f;
    float x;
    float step;
    float t;
    float ab;
    float r;
    float lim;

    if (half < d) {
        x = d - half;
    } else {
        x = 0.0f;
        if (d < low) {
            x = d - low;
        }
    }
    if (!GAMEUTIL_is_nearly_equal_zero(x, a7)) {
        step = -x;
        t = step;
        if (a0 >= 0.0f) {
            step = step * (a0 * dt);
        }
        ab = step;
        if (step < 0.0f) {
            ab = -step;
        }
        if (x < 0.0f) {
            if (t < ab) goto clampcase;
            goto plain;
        }
        if (x < ab) {
clampcase:
            if (step == 0.0f) {
                result += step;
            } else {
                r = x / step;
                if (r < 0.0f) r = -r;
                step = step * r;
                result += step;
            }
        } else {
plain:
            result += step;
        }
    }
    if (a4 != 0.0f) {
        result += a4 * a5 * dt;
    }
    if (a6 > 0.0f) {
        lim = a6 * dt;
        if (result >= 0.0f) {
            if (lim < result) result = lim;
        } else {
            if (lim < -result) result = -lim;
        }
    }
    return result;
}
#endif
