/* The dead-zone zero is pinned to $f0 and negated in place, and vlen3 moves
 * the square root into an FPR inside its asm (as matched GAMECORE length
 * helpers do). */
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
                         "cfc2.ni $2, $vi22
"
                         "mtc1 $2, %0
"
                         : "=f"(d) : "r"(v) : "$2");
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

void GAMEUTIL_get_spring_interpolate_offset3D(float *out, float *cur, float *target, float k, float max_speed, float eps,
                                              float dt)
{
    float diff[4] __attribute__((aligned(16)));
    float len;

    vsub3(diff, target, cur);
    len = vlen3(diff);
    if (!GAMEUTIL_is_nearly_equal_zero(len, eps)) {
        register float w __asm__("$f0") = 0.0f;
        float x = w - len;
        register float res __asm__("$f21") = w;
        float e;
        w = -w;
        if (res < x) e = x - res; else if (x < w) e = x - w; else e = res;

        if (!GAMEUTIL_is_nearly_equal_zero(e, eps)) {
            res += spring_step(e, k, dt);
        }
        res = limit_speed(res, max_speed, dt);
        vscale3(out, diff, res / len);
        out[3] = 0.0f;
    } else {
        *(s128 *)out = ZeroVector;
    }
}
