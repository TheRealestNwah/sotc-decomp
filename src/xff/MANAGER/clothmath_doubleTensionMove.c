typedef int s128 __attribute__((mode(TI)));
static inline float eeSqrt(float x)
{
    float r;
    __asm__("sqrt.s %0, %1" : "=&f"(r) : "f"(x));
    return r;
}
static inline float tensionDir(float *out, float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\nlqc2 vf6, 0x0(%2)\nvsub.xyzw vf8, vf5, vf6\nvmul.xyz vf7, vf8, vf8\n"
                         "vaddy.x vf7, vf7, vf7y\nvaddz.x vf7, vf7, vf7z\nvrsqrt Q, vf0w, vf7x\nsqc2 vf8, 0x0(%3)\n"
                         "vwaitq\ncfc2.ni $2, $22\nmtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b), "r"(out) : "$2", "memory");
    return r;
}
static inline void pullTo(float *out, float *anchor, float *dir, float k)
{
    __asm__ __volatile__("lqc2 vf7, 0x0(%0)\nlqc2 vf5, 0x0(%1)\n" : : "r"(anchor), "r"(dir) : "memory");
    __asm__ __volatile__("qmtc2.ni %0, vf6\nvmulx.xyz vf5, vf5, vf6x\nvadd.xyz vf7, vf7, vf5\nsqc2 vf7, 0x0(%1)\n"
                         : : "r"(k), "r"(out) : "memory");
}
#ifdef NONMATCHING
/* Parked: 41 words differ (1.0f constant hoisting, k temp reg t0, f2 sqrt result). */
void clothmath_doubleTensionMove(s128 *p, float *q, float *anchor, float maxSq, float k, float lim)
{
    struct { s128 sp0; float d1[4]; float d2[4]; float d3[4]; float d4[4]; } L;
    float len;
    float *s1 = (float *)&L.sp0;
    len = tensionDir(L.d1, (float *)p, anchor);
    if (len < lim) {
        pullTo(s1, anchor, L.d1, k * len);
    } else {
        L.sp0 = *p;
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\nlqc2 vf6, 0x0(%2)\nvsub.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%3)\n"
                         "lqc2 vf7, 0x0(%3)\nvmul.xyz vf7, vf7, vf7\nvaddy.x vf7, vf7, vf7y\nvaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\nmtc1 $2, %0\n"
                         : "=f"(len) : "r"(q), "r"(&L.sp0), "r"(L.d2) : "$2", "memory");
    if (maxSq < len) {
        float r = eeSqrt(len);
        float one = 1.0f;
        float t = one - (r - k) / r;
        t = one - t * t;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nqmtc2.ni %1, vf6\nvmulx.xyzw vf5, vf5, vf6x\nsqc2 vf5, 0x0(%2)\n"
                             "lqc2 vf5, 0x0(%3)\nlqc2 vf6, 0x0(%2)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%3)\n"
                             : : "r"(L.d2), "r"(t), "r"(L.d3), "r"(&L.sp0) : "memory");
        len = tensionDir(L.d4, (float *)&L.sp0, anchor);
        if (len < lim) {
            float *s2 = (float *)&L.sp0;
            pullTo(s2, anchor, L.d4, k * len);
        }
    }
    *p = L.sp0;
}
#else
void clothmath_doubleTensionMove(s128 *p, float *q, float *anchor, float maxSq, float k, float lim);
#endif
