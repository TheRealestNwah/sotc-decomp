/* Parked at 25 diffs: the Original builds the dead-zone zero in $f1 and
 * compares against the result register $f21, where gcc propagates $f12
 * everywhere (14 words), and the limit-speed tail loads the
 * GAMEUTIL_get_increase_value arguments in a different order (11 words). */
#ifdef NONMATCHING
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
extern float GAMEUTIL_get_difference_value(int, float, float);
extern float GAMEUTIL_get_increase_value(int, float, float);

static inline float dead_zone(float x, float min, float max)
{
    if (max < x) {
        return x - max;
    }
    if (x < min) {
        return x - min;
    }
    return 0.0f;
}

static inline float spring_step(float e, float k, float dt)
{
    register float step __asm__("$f12") = -e;
    register float ne __asm__("$f2") = step;
    float as;

    if (0.0f <= k) {
        step = step * (k * dt);
    }
    as = step;
    if (step < 0.0f) as = -step;
    if (e < 0.0f ? ne < as : e < as) {
        if (step != 0.0f) {
            float r = e / step;
            float t = step * (r < 0.0f ? -r : r);
            __asm__("" : "+f"(t));
            step = t;
        }
    }
    return step;
}

static inline float limit_speed(float v, float max, float dt)
{
    if (0.0f < max) {
        float lim = max * dt;
        if (0.0f <= v) {
            if (lim < v) {
                v = lim;
            }
        } else if (lim < -v) {
            v = -lim;
        }
    }
    return v;
}

static inline float dead_zone2(float x, float min, float max)
{
    if (max < x) {
        return x - max;
    }
    if (x < min) {
        return x - min;
    }
    return max;
}

static inline float value_extend(float k, float max_speed, float cur, int flag, float target, float eps, float dt)
{
    float d = GAMEUTIL_get_difference_value(flag, cur, target);
    float w = 0.0f;
    register float res __asm__("$f21") = w;
    float e = dead_zone2(w - d, -w, res);

    if (!GAMEUTIL_is_nearly_equal_zero(e, eps)) {
        res += spring_step(e, k, dt);
    }
    if (0.0f < max_speed) {
        float lim = max_speed * dt;
        if (0.0f <= res) {
            if (lim < res) {
                res = lim;
            }
        } else if (lim < -res) {
            res = -lim;
        }
    }
    return GAMEUTIL_get_increase_value(flag, cur, res);
}

static inline float reset_double_spring_interp_cntrl(char *p, float v)
{
    float *b = (float *)(p + 0x18);
    float *a = (float *)(p + 0x1C);
    float t[1];
    int i;

    t[0] = v;
    for (i = 0; i < 1; i++) {
        float f = t[i];
        a[i] = f;
        b[i] = f;
    }
    return *a;
}

float doit_double_spring_interp_cntrl(char *p, int reset, float target, float dt)
{
    float v;

    if (reset == 1) {
        return reset_double_spring_interp_cntrl(p, target);
    }
    v = value_extend(*(float *)(p + 0x0), *(float *)(p + 0x4), *(float *)(p + 0x18), *(int *)(p + 0x14), target, *(float *)(p + 0x10), dt);
    *(float *)(p + 0x18) = v;
    v = value_extend(*(float *)(p + 0x8), *(float *)(p + 0xC), *(float *)(p + 0x1C), *(int *)(p + 0x14), v, *(float *)(p + 0x10), dt);
    *(float *)(p + 0x1C) = v;
    return v;
}
#endif
