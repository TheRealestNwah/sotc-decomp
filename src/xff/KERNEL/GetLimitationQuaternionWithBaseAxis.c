typedef float Vec4[4] __attribute__((aligned(16)));
typedef int s128 __attribute__((mode(TI)));

static inline void quatMul(float *q, float *r)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(q), "r"(r) : "memory");
}

static inline void matFromQuat(float *mat, float *q)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w
"
                         "lqc2 vf11, 0x0(%1)
"
                         "vmr32.w vf14, vf0
"
                         "vmr32.w vf15, vf0
"
                         "vmr32.w vf16, vf0
"
                         "vopmula.xyz ACC, vf11, vf12
"
                         "vmadd.xyz vf11, vf0, vf0
"
                         "vmadd.xyz vf10, vf11, vf12
"
                         "vmul.xyz vf13, vf11, vf10
"
                         "vopmula.xyz ACC, vf11, vf10
"
                         "vmaddw.xyz vf15, vf10, vf11w
"
                         "vmsubw.xyz vf16, vf10, vf11w
"
                         "vopmula.xyz ACC, vf13, vf12
"
                         "vmadd.xyz vf17, vf13, vf12
"
                         "vopmula.xyz ACC, vf15, vf12
"
                         "vmadd.xyz vf15, vf0, vf0
"
                         "vsub.xyz vf14, vf12, vf17
"
                         "vmove.yz vf17, vf14
"
                         "vmove.y vf14, vf16
"
                         "vmove.y vf16, vf15
"
                         "vmove.y vf15, vf17
"
                         "vmove.z vf14, vf15
"
                         "vmove.z vf15, vf16
"
                         "vmove.z vf16, vf17
"
                         "sqc2 vf14, 0x0(%0)
"
                         "sqc2 vf15, 0x10(%0)
"
                         "sqc2 vf16, 0x20(%0)
"
                         : : "r"(mat), "r"(q) : "memory");
}

extern void iosGetArbitraryUpVectorElement(float *, float *);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);
extern float iosGetACosfExact(float);
extern void iosGetSinCosf(float *, float);

static inline void normalize3(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(dst), "r"(src) : "memory");
}

static inline void scaleXYZ(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "qmtc2.ni %1, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(v), "r"(s) : "memory");
}

/* Parked: 18 words off (was ~190). Left: the m pointer lands in $v1 instead of $v0 and the three copies of the result pointer in the second limit block take swapped saved registers. */
#ifdef NONMATCHING
void GetLimitationQuaternionWithBaseAxis(float *out, float *q, float *axis, float limit)
{
    struct { Vec4 mat[4]; Vec4 t; Vec4 diff; Vec4 up; Vec4 sc; Vec4 r; Vec4 neg; Vec4 sc2; } L;
    float a, tw;
    float *m, *tp, *upp, *dp, *dq, *p0, *p1, *p2;

    m = L.mat[0];
    __asm__("" : "+r"(m));
    matFromQuat(m, q);
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"((char *)m + 0x30) : "memory");
    tp = L.t;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)
"
                         "lqc2 vf14, 0x0(%1)
"
                         "lqc2 vf15, 0x10(%1)
"
                         "lqc2 vf16, 0x20(%1)
"
                         "lqc2 vf17, 0x30(%1)
"
                         "vmulax.xyzw ACC, vf14, vf8x
"
                         "vmadday.xyzw ACC, vf15, vf8y
"
                         "vmaddaz.xyzw ACC, vf16, vf8z
"
                         "vmaddw.xyzw vf10, vf17, vf8w
"
                         "sqc2 vf10, 0x0(%2)
"
                         : : "r"(axis), "r"(m), "r"(tp) : "memory");
    upp = L.up;
    iosGetArbitraryUpVectorElement(upp, axis);
    dp = L.diff;
    GetDifferencialQuaternionWithNoRegularize(dp, tp, axis, upp);
    dq = dp;
    a = iosGetACosfExact(L.diff[3]);
    tw = a + a;
    if (tw < 0.0f ? limit < -tw : limit < tw) {
        iosGetSinCosf(L.sc, (tw < 0.0f ? -limit : limit) * 0.5f);
        normalize3(out, dq);
        scaleXYZ(out, L.sc[1]);
        out[3] = L.sc[0];
    } else {
        *(s128 *)out = *(s128 *)L.diff;
    }
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)
"
                         "vsubw.x vf5, vf0, vf0w
"
                         "vmulx.xyz vf11, vf11, vf5x
"
                         "sqc2 vf11, 0x0(%1)
"
                         : : "r"(L.diff), "r"(L.neg) : "memory");
    p1 = L.r;
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
                         : : "r"(L.neg), "r"(q), "r"(p1) : "memory");
    p0 = p1;
    p2 = p1;
    a = iosGetACosfExact(L.r[3]);
    tw = a + a;
    if (tw < 0.0f ? limit < -tw : limit < tw) {
        iosGetSinCosf(L.sc2, (tw < 0.0f ? -limit : limit) * 0.5f);
        normalize3(p0, p2);
        scaleXYZ(p0, L.sc2[1]);
        L.r[3] = L.sc2[0];
    }
    quatMul(out, p1);
}
#else
extern void GetLimitationQuaternionWithBaseAxis(float *out, float *q, float *axis, float limit);
#endif
