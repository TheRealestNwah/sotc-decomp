typedef float Vec4[4] __attribute__((aligned(16)));
typedef int s128 __attribute__((mode(TI)));

extern Vec4 IdentityQuaternion;
extern void GetEulerYXZFromQuaternion(float *, float *, float *, float *);
extern void GetEulerYXZFromQuaternionZHalfPI(float *, float *, float *, float *);
extern void GetQuaternionByEulerYXZ(float *, float, float, float);

/* Parked: 93 words off; structure and both VU blocks follow the asm. Left: register assignment of q/r (original keeps the result buffer pointer in $t1 and q in $a3) and constant rounding of the degree-to-radian factor. */
#ifdef NONMATCHING
void _setNodeHPB(int idx, char *obj, char *base, float *q, int halfPi, float h, float p, float b)
{
    struct { Vec4 r; Vec4 q10; Vec4 e; Vec4 neg; } L;
    float *cur = (float *)(base + idx * 16);
    char *node = *(char **)(obj + 8) + idx * 64;
    float *r;

    if (*(int *)(node + 0x38) >= 0)
        q = IdentityQuaternion;
    r = L.r;
    *(s128 *)L.q10 = *(s128 *)q;
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         "sqc2 vf13, 0x0(%3)\n"
                         : : "r"(L.q10), "r"(L.neg), "r"(cur), "r"(r) : "memory");
    if (halfPi)
        GetEulerYXZFromQuaternionZHalfPI(L.e, r, cur, q);
    else
        GetEulerYXZFromQuaternion(L.e, r, cur, q);
    L.e[0] += -p * 0.017453292f;
    L.e[1] += h * 0.017453292f;
    L.e[2] += b * 0.017453292f;
    GetQuaternionByEulerYXZ(r, L.e[0], L.e[1], L.e[2]);
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
                         "sqc2 vf13, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%2)\n"
                         : : "r"(L.q10), "r"(r), "r"(cur) : "memory");
}
#else
extern void _setNodeHPB(int idx, char *obj, char *base, float *q, int halfPi, float h, float p, float b);
#endif
