#ifdef NONMATCHING /* zero/dead-zone register allocation differs in prologue */
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
    float step = -e;
    float as;

    if (0.0f <= k) {
        step = step * (k * dt);
    }
    as = step < 0.0f ? -step : step;
    if (e < 0.0f ? -e < as : e < as) {
        if (step != 0.0f) {
            float r = e / step;
            return step * (r < 0.0f ? -r : r);
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
    float e = dead_zone(cur - target, -w, w);
    float res = w;

    if (!GAMEUTIL_is_nearly_equal_zero(e, eps)) {
        res += spring_step(e, k, dt);
    }
    return limit_speed(res, max_speed, dt);
}
#endif
