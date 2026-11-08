typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern float XUnitVector[];
extern float YUnitVector[];
extern float ZUnitVector[];
extern void iosGetSinCosf(float *, float);

static inline void quatMul(float *q, float *r)
{
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
                         "sqc2 vf13, 0x0(%0)
"
                         : : "r"(q), "r"(r) : "memory");
}

static inline void rotAxis(float *q, float angle, float *axis, float *rot, float *sc)
{
    iosGetSinCosf(sc, -angle * 0.5f);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "qmtc2.ni %1, vf6
"
                         "vmulx.xyzw vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%2)
"
                         : : "r"(axis), "r"(sc[1]), "r"(rot) : "memory");
    rot[3] = sc[0];
    quatMul(q, rot);
}

/* Parked: 1 word differs (the first axis block's quaternion multiply reads the rotation temp as 0($sp); the compiler uses the saved copy $s0 instead). */
#ifdef NONMATCHING
void GetQuaternionByEulerZXYExact(float *q, float x, float y, float z)
{
    struct { Vec4 r0; float s0[4] __attribute__((aligned(16))); Vec4 r1; float s1[4] __attribute__((aligned(16))); Vec4 r2; float s2[4] __attribute__((aligned(16))); } B;
    int changed = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(q) : "memory");
    if (z != 0.0f) {
        rotAxis(q, z, ZUnitVector, B.r0.f, B.s0);
        changed = 1;
    }
    if (x != 0.0f) {
        rotAxis(q, x, XUnitVector, B.r1.f, B.s1);
        changed = 1;
    }
    if (y != 0.0f) {
        rotAxis(q, y, YUnitVector, B.r2.f, B.s2);
        changed = 1;
    }
    if (changed) {
        __asm__ __volatile__("lqc2 vf14, 0x0(%0)
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
                             "sqc2 vf15, 0x0(%0)
"
                             : : "r"(q) : "memory");
    }
}
#else
extern void GetQuaternionByEulerZXYExact(float *q, float x, float y, float z);
#endif
