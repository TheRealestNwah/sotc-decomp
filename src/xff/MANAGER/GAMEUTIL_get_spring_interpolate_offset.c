#ifdef NONMATCHING
/* 15 diffs: the dead-zone zero is built in f12 (f1 in value_extend) instead of f0,
 * so the prologue/dead-zone registers and their scheduling differ. */
extern int GAMEUTIL_is_nearly_equal_zero(float, float);

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

float GAMEUTIL_get_spring_interpolate_offset(float k, float max_speed, float cur, float target, float eps, float dt)
{
    float w = 0.0f;
    register float res __asm__("$f21") = w;
    float e = dead_zone(cur - target, -w, res);

    if (!GAMEUTIL_is_nearly_equal_zero(e, eps)) {
        res += spring_step(e, k, dt);
    }
    return limit_speed(res, max_speed, dt);
}
#endif
