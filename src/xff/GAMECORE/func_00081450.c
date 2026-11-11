extern char *GetLayoutClass(int);
extern long fptodp(float);
extern int dpcmp(long, double);

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

static int func_00081450(float *p, int layout)
{
    register double k __asm__("$5");
    float *q;
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    char *lc = GetLayoutClass(layout);
    int ok = 0;
    int ok2;
    float d;
    register float sq __asm__("$f0");
    register long dp __asm__("$4");

    XFORM(v, p, *(char **)(lc + 0x164) + 0x180);
    if (v[2] < 0.0f && v[0] > -0.07f) {
        v[0] = -0.07f;
        __asm__ __volatile__("" : : : "memory");
        XFORM(p, v, *(char **)(lc + 0x158) + 0x180);
        ok = 1;
    }
    q = w;
    XFORM(q, p, *(char **)(lc + 0x164) + 0x140);
    if (0.0f > w[2]) {
        __asm__ __volatile__("lqc2 vf7, 0x0(%1)
"
                             "vmul.xy vf7, vf7, vf7
"
                             "vaddy.x vf7, vf7, vf7y
"
                             "qmfc2.ni $2, vf7
"
                             "mtc1 $2, %0
"
                             : "=f"(d) : "r"(q) : "$2");
        if (d < 0.0048999987f) {
            __asm__ __volatile__("sqrt.s %0, %1" : "=f"(sq) : "f"(d));
            d = 0.07f / sq;
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                                 "mfc1 $8, %0
"
                                 "qmtc2.ni $8, vf6
"
                                 "vmulx.xy vf5, vf5, vf6x
"
                                 "sqc2 vf5, 0x0(%1)
"
                                 : : "f"(d), "r"(q) : "$8", "memory");
            XFORM(p, q, *(char **)(lc + 0x158) + 0x140);
            ok |= 1;
        }
    }
    ok2 = 0;
    dp = fptodp(p[1]);
    k = 9.01;
    __asm__ __volatile__("" : "+r"(dp));
    if (dpcmp(dp, k) < 0) {
        p[1] = 9.01f;
        ok2 = 1;
    }
    return ok | ok2;
}
