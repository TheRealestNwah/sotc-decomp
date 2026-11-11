extern int (*D_0017AEC0)(void *, int, void *);
extern int D_0017AEC4;

static inline float rsqrtDist(float *dst, float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vsub.xyzw vf8, vf5, vf6\n"
                         "vmul.xyz vf7, vf8, vf8\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vrsqrt Q, vf0w, vf7x\n"
                         "sqc2 vf8, 0x0(%1)\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(dst), "r"(a), "r"(b) : "$2", "memory");
    return r;
}

static inline void pushOut(float *p0, float *p1, float *d, float s)
{
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "vadd.xyz vf7, vf7, vf5\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(p0), "r"(p1), "r"(d), "f"(s) : "$8", "memory");
}

#define XFORM(dst, src, m)                                  \
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"             \
                         "lqc2 vf14, 0x0(%2)\n"            \
                         "lqc2 vf15, 0x10(%2)\n"           \
                         "lqc2 vf16, 0x20(%2)\n"           \
                         "lqc2 vf17, 0x30(%2)\n"           \
                         "vmulax.xyzw ACC, vf14, vf8x\n"   \
                         "vmadday.xyzw ACC, vf15, vf8y\n"  \
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"  \
                         "vmaddw.xyzw vf10, vf17, vf8w\n"  \
                         "sqc2 vf10, 0x0(%0)\n"            \
                         : : "r"(dst), "r"(src), "r"(m) : "memory")

static void func_000800B8(char *c, char *lc)
{
    float tmp[4] __attribute__((aligned(16)));
    float tmp2[4] __attribute__((aligned(16)));
    float tmp3[4] __attribute__((aligned(16)));
    int ok = 0;
    char *cb = *(char **)c;
    char *ca = *(char **)(c + 0xC);
    char *lim = *(char **)(cb + 0x28);
    char *s1 = *(char **)(ca + 0x10);
    char *s0 = s1 + 0x10;
    float k = *(float *)(lim + 4);
    float lo = *(float *)(lim + 8);
    float r;
    float d;

    r = rsqrtDist(tmp, (float *)s0, (float *)s1);
    if (r < lo)
        pushOut((float *)s0, (float *)s1, tmp, k * r);
    XFORM(tmp2, s0, *(char **)(lc + 0x164));
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xy vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(tmp2) : "$2");
    if (d < 0.0224999972f) {
        register float sq __asm__("$f0");
        __asm__ __volatile__("sqrt.s %0, %1" : "=f"(sq) : "f"(d));
        d = 0.15f / sq;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "mfc1 $8, %0\n"
                             "qmtc2.ni $8, vf6\n"
                             "vmulx.xy vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             : : "f"(d), "r"(tmp2) : "$8", "memory");
        XFORM(s0, tmp2, *(char **)(lc + 0x158));
        ok = 1;
    }
    ok |= D_0017AEC0(s0, D_0017AEC4, s1);
    if (ok != 0) {
        r = rsqrtDist(tmp3, (float *)s0, (float *)s1);
        if (r < lo)
            pushOut((float *)s0, (float *)s1, tmp3, k * r);
    }
}
