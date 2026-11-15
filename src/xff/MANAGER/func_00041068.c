#ifdef NONMATCHING /* 80 diffs: loop-invariant constants/pointers (s4/s5) and t1/a3/f0 register choices */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

typedef struct {
    char pad0[0x80];
    float rot80[4];
    char pad90[0x2E4 - 0x90];
    Vec4 *quats;
    char pad2E8[0x34C - 0x2E8];
    Vec4 *positions;
    char pad350[0x358 - 0x350];
    int *options;
    char pad35C[0x724 - 0x35C];
    float blend;
} Cls;

extern int GetMotionOptionNodeParentId(void *, int);
extern int GetCharacterClassOptionNodeLocalQuaternionPos(Vec4 *, Vec4 *, Cls *, int, int);

void func_00041068(Cls *c)
{
    Vec4 buf[6];
    int *opt = c->options;
    int n = 0;
    int i;
    float *t1;
    float *a3;
    float *s4;
    union { float f; int i; } ti;

    if (opt)
        n = opt[8];
    for (i = 0; i < n; i++) {
        Vec4 *a2;
        Vec4 *a0;
        float t;
        float dot;
        s4 = buf[2].f;

        if (GetMotionOptionNodeParentId(opt, i) >= 0)
            continue;
        GetCharacterClassOptionNodeLocalQuaternionPos(&buf[0], &buf[1], c, i, 1);
        t1 = buf[3].f;
        __asm__ __volatile__("lqc2 vf11, 0x0(%0)
"
                             "lqc2 vf12, 0x0(%1)
"
                             "vmul.xyzw vf13, vf11, vf12
"
                             "vaddy.x vf13, vf13, vf13y
"
                             "vaddz.x vf13, vf13, vf13z
"
                             "vsubx.w vf13, vf13, vf13x
"
                             "vmulw.xyz vf14, vf12, vf11w
"
                             "vmulw.xyz vf15, vf11, vf12w
"
                             "vopmula.xyz ACC, vf12, vf11
"
                             "vopmsub.xyz vf16, vf11, vf12
"
                             "vadd.xyz vf13, vf14, vf15
"
                             "vadd.xyz vf13, vf13, vf16
"
                             "sqc2 vf13, 0x0(%2)
"
                             : : "r"(c->rot80), "r"(&buf[0]), "r"(t1) : "memory");
        t = c->blend;
        a0 = (Vec4 *)((char *)c->positions + (i << 4));
        a2 = (Vec4 *)((char *)c->quats + (i << 4));
        buf[2].q = buf[1].q;
        if (t < 1.0f) {
            a3 = buf[4].f;
            buf[4].q = a2->q;
            __asm__ __volatile__("lqc2 vf14, 0x0(%1)
"
                                 "lqc2 vf15, 0x0(%2)
"
                                 "vmul.xyzw vf15, vf14, vf15
"
                                 "vaddy.x vf15, vf15, vf15y
"
                                 "vaddz.x vf15, vf15, vf15z
"
                                 "vaddw.x vf15, vf15, vf15w
"
                                 "qmfc2.ni $2, vf15
"
                                 "mtc1 $2, %0
"
                                 : "=f"(dot) : "r"(t1), "r"(a3) : "$2", "memory");
            buf[5].f[0] = dot;
            if (buf[5].i[0] < 0)
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                                     "qmtc2.ni %1, vf6
"
                                     "vmulx.xyzw vf5, vf5, vf6x
"
                                     "sqc2 vf5, 0x0(%0)
"
                                     : : "r"(a3), "r"(0xBF800000) : "memory");
            ti.f = t;
            __asm__ __volatile__("qmtc2.ni %0, vf7
"
                                 "lqc2 vf5, 0x0(%1)
"
                                 "lqc2 vf6, 0x0(%2)
"
                                 "vsubx.w vf8, vf0, vf7x
"
                                 "vmulax.xyzw ACC, vf5, vf7x
"
                                 "vmaddw.xyzw vf9, vf6, vf8w
"
                                 "sqc2 vf9, 0x0(%3)
"
                                 "lqc2 vf14, 0x0(%3)
"
                                 "vmul.xyzw vf15, vf14, vf14
"
                                 "vaddy.x vf15, vf15, vf15y
"
                                 "vaddz.x vf15, vf15, vf15z
"
                                 "vaddw.x vf15, vf15, vf15w
"
                                 "vrsqrt Q, vf0w, vf15x
"
                                 "vwaitq
"
                                 "vmulq.xyzw vf15, vf14, Q
"
                                 "sqc2 vf15, 0x0(%3)
"
                                 : : "r"(ti.i), "r"(t1), "r"(a3), "r"(a2) : "memory");
            __asm__ __volatile__("qmtc2.ni %0, vf7
"
                                 "lqc2 vf5, 0x0(%1)
"
                                 "lqc2 vf6, 0x0(%2)
"
                                 "vsubx.w vf8, vf0, vf7x
"
                                 "vmulax.xyz ACC, vf5, vf7x
"
                                 "vmaddw.xyz vf5, vf6, vf8w
"
                                 "sqc2 vf5, 0x0(%2)
"
                                 : : "r"(ti.i), "r"(s4), "r"(a0) : "memory");
        } else {
            a2->q = buf[3].q;
            a0->q = buf[2].q;
        }
    }
}
#endif
