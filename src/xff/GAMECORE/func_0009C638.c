typedef int s128 __attribute__((mode(TI)));

extern char XUnitVector[], YUnitVector[], ZUnitVector[];
extern float iosGetACosfExact(float);
extern void iosAbsVector(void *, void *);
extern float AI_GetAccelA(float, float, float, float);
extern float AI_GetAccelB(float, float, float, float);

#ifdef NONMATCHING /* 76 diffs: o lands in $s2 not $s0 (orig o=$s0, o+0x160=$s1, v=$s2), axis-pick branch layout */
static void func_0009C638(char *o, float *v, float t)
{
    float ab[4] __attribute__((aligned(16)));
    float d;
    char *axis;
    float b;
    int idx;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(v), "r"(o + 0x160) : "$2");
    if (d >= 0.99f) {
        *(float *)(o + 0x260) = 0.0f;
    } else if (d <= -0.99f) {
        iosAbsVector(ab, o + 0x160);
        *(float *)(o + 0x260) = 3.1415927f;
        if (ab[1] < ab[0] && ab[2] < ab[0])
            idx = 0;
        else if (ab[2] < ab[1])
            idx = 1;
        else
            idx = 2;
        switch (idx) {
        case 0: axis = YUnitVector; break;
        case 1: axis = ZUnitVector; break;
        default: axis = XUnitVector; break;
        }
        *(s128 *)(o + 0x250) = *(s128 *)axis;
    } else {
        *(float *)(o + 0x260) = iosGetACosfExact(d);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vopmula.xyz ACC, vf5, vf6\n"
                             "vopmsub.xyz vf7, vf6, vf5\n"
                             "vsub.w vf7, vf7, vf7\n"
                             "sqc2 vf7, 0x0(%0)\n"
                             : : "r"(o + 0x250), "r"(v), "r"(o + 0x160) : "memory");
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(o + 0x250) : "memory");
    b = AI_GetAccelB(0.0f, 0.0f, *(float *)(o + 0x260), t);
    *(float *)(o + 0x268) = b;
    *(float *)(o + 0x264) = AI_GetAccelA(0.0f, 0.0f, t, b);
}
#endif
