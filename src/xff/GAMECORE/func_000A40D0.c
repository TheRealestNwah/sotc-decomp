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

#ifdef NONMATCHING /* 77 diffs: saved-register pairs (o+0x240 $s2 vs $s1), volatile layout-pointer re-read order, sqrt.s operand regs */
void func_000A40D0(float r, char *o, float *out0, char *obj0, int sign)
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
            lay = GetLayoutClass(thr);
            *(s128 *)f = **(s128 *volatile *)(lay + 0x134);
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vadd.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(g), "r"(*(char *volatile *)(lay + 0x134)), "r"(o + 0x240) : "memory");
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
                                 : "=f"(k) : "r"(c), "r"(e) : "$2");
            k = r * r - k;
            __asm__("sqrt.s %0, %1" : "=f"(k) : "f"(k));
            *(s128 *)d = *(s128 *)(o + 0x240);
            scale4to(d, d, k);
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
            *(s128 *)a = *(s128 *)(o + 0x240);
        } else {
            scale4to(a, a, -1.0f);
        }
    }
    if (diff < 0.0f ? sign > 0 : sign < 0)
        axis = YUnitVectorInv;
    else
        axis = YUnitVector;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(b), "r"(axis), "r"(a) : "memory");
    s = diff;
    if (s < 0.0f)
        s = -s;
    t = AI_GetAreaDistScale2(*(float *)(*(char **)(o + 0x20) + 0xC), s);
    {
        int ti;
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
#endif
