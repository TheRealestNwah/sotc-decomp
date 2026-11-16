typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroVector;
extern int GAMEUTIL_is_nearly_equal_zero3D(float *, float);
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
extern void func_000E26E8(float *a, float *b, float *v, char **pp, float fa, float fb);
extern void func_000DF598(float *dst, char *w, float *v, char **pp);
extern float func_000E27F0(float *vec, char **pp);

static inline void vecScale3(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd3(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static void func_000E24B8(int *outA, int *outB, char *w, char **p, float t)
{
    float v[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    float fa, fb;
    float base;
    float r;
    char *q = (char *)p + 0x60;

    base = *(float *)(w + 0x1A0) * *(float *)(w + 0x1A4) * *(float *)(w + 0x1A8) * *(float *)(w + 0x1AC);
    fa = base * *(float *)(*p + 0x68);
    fb = base * *(float *)(*p + 0x80);
    if (t == 0.0f)
        *(s128 *)v = ZeroVector;
    else
        *(s128 *)v = *(s128 *)(w + 0x1F0);
    func_000E26E8(&fa, &fb, v, p, fa, fb);
    func_000DF598(dir, w, v, p);
    r = func_000E27F0(dir, p);
    fa = fa * r;
    vecScale3(tmp, dir, fa);
    tmp[1] = 0.0f;
    *outA = GAMEUTIL_is_nearly_equal_zero3D(tmp, 0.003f) == 0;
    vecAdd3((float *)(w + 0x180), (float *)(q + 0x10), tmp);
    vecScale3(tmp, v, fb);
    tmp[0] = tmp[2] = 0.0f;
    *outB = GAMEUTIL_is_nearly_equal_zero(tmp[1], 0.003f) == 0;
    vecAdd3((float *)(w + 0x190), (float *)(q + 0x10), tmp);
    *(s128 *)(w + 0x170) = *(s128 *)(q + 0x10);
}
