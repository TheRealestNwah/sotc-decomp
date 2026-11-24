#ifdef NONMATCHING
/* Parked: 8 diffs, same size.
 * Remaining: the tail call to GAMEUTIL_get_increase_value sets $a0 (flag) before
 * $f12/$f13, where the Original sets them first and $a0 last, next to the $s0 restore. */
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
extern float GAMEUTIL_get_difference_value(int, float, float);
extern float GAMEUTIL_get_increase_value(int, float, float);

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

float GAMEUTIL_get_spring_interpolate_value_extend(int flag, float k, float max_speed, float cur, float target, float eps, float dt)
{
    float d = GAMEUTIL_get_difference_value(flag, cur, target);
    register float w __asm__("$f1") = 0.0f;
    float x = w - d;
    register float res __asm__("$f21") = w;
    float e;
    w = -w;
    if (res < x) {
        e = x - res;
    } else if (x < w) {
        e = x - w;
    } else {
        e = res;
    }

    if (!GAMEUTIL_is_nearly_equal_zero(e, eps)) {
        res += spring_step(e, k, dt);
    }
    return GAMEUTIL_get_increase_value(flag, cur, limit_speed(res, max_speed, dt));
}
#endif
