typedef float Vec4[4] __attribute__((aligned(16)));
typedef int s128 __attribute__((mode(TI)));

extern Vec4 IdentityQuaternion;
extern Vec4 XUnitVector;
extern Vec4 YUnitVector;
extern Vec4 ZUnitVector;
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);

static inline void qmul(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

/* Parked: 20 words off (was ~150); only scheduling of the node/cur address setup and of the lui/addiu pairs for the axis vectors differ. The stack-pointer launder recipe applies. */
#ifdef NONMATCHING
void _setNodeHPBIllegal(int idx, char *obj, char *base, float *q, float h, float p, float b)
{
    struct { Vec4 a; Vec4 neg; Vec4 c; Vec4 r1; Vec4 r2; Vec4 r3; } L;
    float *cur = (float *)(base + idx * 16);
    float *x = (float *)obj;
    char *node = *(char **)(obj + 8) + idx * 64;

    if (*(int *)(node + 0x38) >= 0) {
        x = (float *)(node + 0x20);
        q = IdentityQuaternion;
    }
    qmul(L.a, q, x);
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%1)\n"
                         : : "r"(L.a), "r"(L.neg) : "memory");
    qmul(L.c, L.neg, cur);
    *(s128 *)cur = *(s128 *)L.a;
    {
        short a1 = (short)(h * 182.04444f);
        float *p1, *p2;
        p1 = L.r1;
        __asm__("" : "+r"(p1));
        SetQuaternionByAxisRotateVWithNoRegularize(p1, -a1, YUnitVector);
        p2 = L.r1;
        __asm__("" : "+r"(p2));
        qmul(cur, cur, p2);
    }
    {
        short a2 = (short)(-p * 182.04444f);
        float *p1, *p2;
        p1 = L.r2;
        __asm__("" : "+r"(p1));
        SetQuaternionByAxisRotateVWithNoRegularize(p1, -a2, XUnitVector);
        p2 = L.r2;
        __asm__("" : "+r"(p2));
        qmul(cur, cur, p2);
    }
    {
        short a3 = (short)(b * 182.04444f);
        float *p1, *p2;
        p1 = L.r3;
        __asm__("" : "+r"(p1));
        SetQuaternionByAxisRotateVWithNoRegularize(p1, -a3, ZUnitVector);
        p2 = L.r3;
        __asm__("" : "+r"(p2));
        qmul(cur, cur, p2);
    }
    qmul(cur, cur, L.c);
}
#else
extern void _setNodeHPBIllegal(int idx, char *obj, char *base, float *q, float h, float p, float b);
#endif
