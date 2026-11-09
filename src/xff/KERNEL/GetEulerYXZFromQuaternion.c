typedef float Vec4[4] __attribute__((aligned(16)));

extern Vec4 XUnitVector;
extern Vec4 YUnitVector;
extern Vec4 ZUnitVector;
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);

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

extern void iosGetStabXZVector(float *, float *);
extern float iosGetATan2fExact(float, float);
extern float iosGetASinfExact(float);

static inline void axisA(float *dst, float *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)
"
                         "vmul.xyzw vf5, vf4, vf4
"
                         "vmr32.xyzw vf6, vf4
"
                         "vmul.xyzw vf7, vf6, vf4
"
                         "vmr32.xyzw vf6, vf6
"
                         "vmul.xyzw vf8, vf6, vf4
"
                         "vsubx.z vf6, vf0, vf5x
"
                         "vsuby.z vf6, vf6, vf5y
"
                         "vaddw.y vf6, vf7, vf7w
"
                         "vsuby.x vf6, vf8, vf8y
"
                         "vsub.w vf6, vf0, vf0
"
                         "vadd.w vf5, vf0, vf0
"
                         "vmulw.xyz vf6, vf6, vf5w
"
                         "vaddw.z vf6, vf6, vf0w
"
                         "sqc2 vf6, 0x0(%0)
"
                         : : "r"(dst), "r"(q) : "memory");
}

static inline void axisB(float *dst, float *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)
"
                         "vmul.xyzw vf5, vf4, vf4
"
                         "vmr32.xyzw vf6, vf4
"
                         "vmul.xyzw vf7, vf6, vf4
"
                         "vaddy.z vf6, vf0, vf7y
"
                         "vsubw.z vf6, vf6, vf7w
"
                         "vsubx.y vf6, vf0, vf5x
"
                         "vsubz.y vf6, vf6, vf5z
"
                         "vaddz.x vf6, vf7, vf7z
"
                         "vsub.w vf6, vf0, vf0
"
                         "vadd.w vf5, vf0, vf0
"
                         "vmulw.xyz vf6, vf6, vf5w
"
                         "vaddw.y vf6, vf6, vf0w
"
                         "sqc2 vf6, 0x0(%0)
"
                         : : "r"(dst), "r"(q) : "memory");
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
/* Parked: 17 words off (was 63). Launder recipe applied; what is left is the order of the t0/r pointer setup, the neg/sll order of the negated short angle and swapped $v0/$v1 for the matrix pointers. */
/* Parked: 13 words off (was 63): placement of the changed=0 load and swapped $v0/$v1 for the matrix pointers. */
/* Parked: 5 words off (was 63); only $v0/$v1 for the matrix-pointer temporaries differ (the original keeps the matrix base in $v1 and the mat[3] address fresh in $v0). */
#ifdef NONMATCHING
void GetEulerYXZFromQuaternion(float *out, float *q)
{
    struct { Vec4 a; Vec4 b; Vec4 c; Vec4 mat[4]; Vec4 r; Vec4 t0; Vec4 t1; Vec4 t2; } L;
    float *rp, *ax, *p1, *p2, *m1, *m2, *t0p;
    int changed;
    float zero;
    float x;
    float y;

    axisA(L.a, q);
    ax = L.c;
    axisB(ax, q);
    iosGetStabXZVector(L.b, L.a);
    zero = 0.0f;
    out[1] = iosGetATan2fExact(L.b[0], L.b[2]);
    x = -iosGetASinfExact(L.a[1]);
    y = out[1];
    out[0] = x;
    t0p = L.t0;
    rp = L.r;
    changed = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(rp) : "memory");
    if (y != zero) {
        { short a0 = (short)(y * 32768.0f / 3.14159274f); SetQuaternionByAxisRotateVWithNoRegularize(L.t0, -a0, YUnitVector); }
        quatMul(L.r, t0p);
        changed = 1;
    }
    if (x != zero) {
        p1 = L.t1;
        __asm__("" : "+r"(p1));
        { short a1 = (short)(x * 32768.0f / 3.14159274f); SetQuaternionByAxisRotateVWithNoRegularize(p1, -a1, XUnitVector); }
        p2 = L.t1;
        __asm__("" : "+r"(p2));
        quatMul(L.r, p2);
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
                             : : "r"(L.r) : "memory");
    }
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)
"
                         "vsubw.x vf5, vf0, vf0w
"
                         "vmulx.xyz vf11, vf11, vf5x
"
                         "sqc2 vf11, 0x0(%0)
"
                         : : "r"(L.r) : "memory");
    m1 = L.mat[0];
    __asm__("" : "+r"(m1));
    matFromQuat(m1, L.r);
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"((char *)m1 + 0x30) : "memory");
    m2 = L.mat[0];
    __asm__("" : "+r"(m2));
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)
"
                         "lqc2 vf14, 0x0(%0)
"
                         "lqc2 vf15, 0x10(%0)
"
                         "lqc2 vf16, 0x20(%0)
"
                         "lqc2 vf17, 0x30(%0)
"
                         "vmulax.xyzw ACC, vf14, vf8x
"
                         "vmadday.xyzw ACC, vf15, vf8y
"
                         "vmaddaz.xyzw ACC, vf16, vf8z
"
                         "vmaddw.xyzw vf10, vf17, vf8w
"
                         "sqc2 vf10, 0x0(%1)
"
                         : : "r"(m2), "r"(ax) : "memory");
    out[2] = -iosGetATan2fExact(L.c[0], L.c[1]);
    ((int *)out)[3] = 0;
}
#else
extern void GetEulerYXZFromQuaternion(float *out, float *q);
#endif
