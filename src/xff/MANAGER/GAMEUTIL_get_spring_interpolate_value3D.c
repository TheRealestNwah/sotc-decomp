#ifdef NONMATCHING
/* 11 diffs: the dead-zone zero is built in f12 (f1 in value_extend) instead of f0,
 * so the prologue/dead-zone registers and their scheduling differ. */
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

typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroVector;

static inline void vsub3(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vadd3(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vlen3(float *v)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22
"
                         : "=r"(d) : "r"(v));
    return d;
}

static inline void vscale3(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

void GAMEUTIL_get_spring_interpolate_value3D(float *out, float *cur, float *target, float k, float max_speed, float eps,
                                             float dt)
{
    float vel[4] __attribute__((aligned(16)));
    float diff[4] __attribute__((aligned(16)));
    float len;
    float *pv = vel;

    vsub3(diff, target, cur);
    len = vlen3(diff);
    if (!GAMEUTIL_is_nearly_equal_zero(len, eps)) {
        float w = 0.0f;
        register float res __asm__("$f21") = w;
        float e = dead_zone(w - len, -w, w);

        if (!GAMEUTIL_is_nearly_equal_zero(e, eps)) {
            res += spring_step(e, k, dt);
        }
        res = limit_speed(res, max_speed, dt);
        vscale3(pv, diff, res / len);
        pv[3] = 0.0f;
    } else {
        *(s128 *)vel = ZeroVector;
    }
    vadd3(out, cur, vel);
}
#endif
