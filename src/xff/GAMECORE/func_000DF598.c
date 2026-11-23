typedef int s128 __attribute__((mode(TI)));
extern char *GetLayoutClass(int);
extern float iosGetACosfExact(float);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern void iosRotMatrixY(float *, float);

static inline void vnorm(float *p)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(p) : "memory");
}

static inline void vsub3(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vdot(float *a, float *b)
{
    float dot;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static inline void vcross(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vapply(float *out, float *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static void func_000DF598(float *dst, char *w, float *v, char **pp)
{
    float d0[4] __attribute__((aligned(16)));
    float d1[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float m[16] __attribute__((aligned(16)));
    float a0, a1, r;
    char *lc;

    a0 = *(float *)(*pp + 0x70) * 0.017453292519943295f;
    a1 = *(float *)(*pp + 0x74) * 0.017453292519943295f;
    *(s128 *)d0 = *(s128 *)((char *)pp + 0xC0);
    d0[1] = 0.0f;
    vnorm(d0);
    lc = GetLayoutClass(*(int *)((char *)pp + 0x23C));
    vsub3(d1, *(float **)(lc + 0x134), (float *)((char *)pp + 0xA0));
    d1[1] = 0.0f;
    vnorm(d1);
    *(float *)(w + 0x1B0) = iosGetACosfExact(vdot(d0, d1));
    if (a0 >= 0.0f && a1 >= 0.0f)
        *(float *)(w + 0x1B4) = GAMEUTIL_get_dist_ratio(*(float *)(w + 0x1B0), a0, a1);
    else
        *(float *)(w + 0x1B4) = 0.0f;
    vcross(c, d0, d1);
    if (c[1] < 0.0f)
        *(float *)(w + 0x1B4) = -*(float *)(w + 0x1B4);
    r = *(float *)(w + 0x1B4) * (*(float *)(*pp + 0x78) * 0.017453292519943295f);
    *(float *)(w + 0x1B8) = r;
    if (r != 0.0f) {
        iosRotMatrixY(m, r);
        vapply(dst, m, v);
    } else {
        *(s128 *)dst = *(s128 *)v;
    }
}
