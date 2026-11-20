typedef int s128 __attribute__((mode(TI)));

extern char YUnitVector[], YUnitVectorInv[];
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void AI_GetHitPosPerpendicular(float *, float *, float *, float *, int);
extern float AI_GetAreaDistScale2(float, float);
extern int AI_CheckNormZero(void *);

static inline void normalize3(float *v)
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
                         : : "r"(v) : "memory");
}

static inline void scale4to(float *dst, float *v, float s)
{
    int si;
    __asm__ __volatile__("mfc1 %0, %1" : "=r"(si) : "f"(s));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(v), "r"(si), "r"(dst) : "memory");
}

static inline void cross3(float *dst, char *x, float *y)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vopmula.xyz ACC, vf5, vf6
"
                         "vopmsub.xyz vf7, vf6, vf5
"
                         "vsub.w vf7, vf7, vf7
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(dst), "r"(x), "r"(y) : "memory");
}

static void func_000A40D0(float r, char *o, float *out0, char *obj0, int sign)
{
    register float *out __asm__("$19") = out0;
    register char *obj __asm__("$20") = obj0;
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));
    float g[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float diff, t, s, k;
    char *lay, *axis;
    void *thr = isysGetThisSubThread();

    diff = *(float *)(obj + 0x44) - r;
    *(s128 *)a = *(s128 *)(obj + 0x30);
    if (diff < 0.0f) {
        if (*(float *)(o + 0x298) < 3.0f) {
            char *q = o + 0x240;
            lay = GetLayoutClass(thr);
            *(volatile s128 *)f = **(volatile s128 *volatile *)(lay + 0x134);
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vadd.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(g), "r"(*(char *volatile *)(lay + 0x134)), "r"(q) : "memory");
            *(s128 *)e = *(s128 *)obj;
            AI_GetHitPosPerpendicular(c, e, f, g, 0);
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "vmul.xyz vf7, vf7, vf7\n"
                                 "vaddy.x vf7, vf7, vf7y\n"
                                 "vaddz.x vf7, vf7, vf7z\n"
                                 "qmfc2.ni $2, vf7\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(t) : "r"(c), "r"(e) : "$2");
            {
                register float kk __asm__("$f0") = r * r - t;
                __asm__ __volatile__("sqrt.s %0, %1" : "=f"(kk) : "f"(kk));
                scale4to(d, (float *)q, kk);
            }
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vadd.xyzw vf7, vf5, vf6\n"
                                 "sqc2 vf7, 0x0(%1)\n"
                                 : : "r"(c), "r"(d) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "sqc2 vf7, 0x0(%0)\n"
                                 : : "r"(a), "r"(obj), "r"(d) : "memory");
            a[1] = 0.0f;
            normalize3(a);
            *(s128 *)a = *(s128 *)q;
        } else {
            {
                int si;
                float m = -1.0f;
                __asm__ __volatile__("mfc1 %0, %1" : "=r"(si) : "f"(m));
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                                     "qmtc2.ni %1, vf6
"
                                     "vmulx.xyzw vf5, vf5, vf6x
"
                                     "sqc2 vf5, 0x0(%0)
"
                                     : : "r"(a), "r"(si) : "memory");
            }
        }
    }
    if ((diff < 0.0f ? -sign : sign) >= 0)
        cross3(b, YUnitVector, a);
    else
        cross3(b, YUnitVectorInv, a);
    k = *(float *)(*(char **)(o + 0x20) + 0xC);
    s = diff;
    if (s < 0.0f)
        s = -s;
    t = AI_GetAreaDistScale2(k, s);
    {
        register int ti __asm__("$8");
        __asm__ __volatile__("mfc1 %0, %1" : "=r"(ti) : "f"(t));
        __asm__ __volatile__("qmtc2.ni %3, vf7\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsubx.w vf8, vf0, vf7x\n"
                             "vmulax.xyzw ACC, vf5, vf7x\n"
                             "vmaddw.xyzw vf9, vf6, vf8w\n"
                             "sqc2 vf9, 0x0(%0)\n"
                             : : "r"(out), "r"(a), "r"(b), "r"(ti) : "memory");
    }
    if (AI_CheckNormZero(out))
        normalize3(out);
    else
        *(s128 *)out = *(s128 *)(o + 0x240);
}
