typedef float Vec4[4] __attribute__((aligned(16)));

typedef struct Chr {
    char pad0[0xC0];
    char gp[0x124 - 0xC0];
    int f124;
    char pad128[0x134 - 0x128];
    float *f134;
    char pad138[4];
    float *f13C;
    char pad140[0x19C - 0x140];
    char *f19C;
    char pad1A0[0x6D0 - 0x1A0];
    Vec4 f6D0;
    char pad6E0[0xA00 - 0x6E0];
    Vec4 fA00;
    char padA10[0xA27 - 0xA10];
    char fA27;
} Chr;

extern Vec4 YUnitVector;
extern Chr *GetCharacterClass(void);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, float *, float *);
extern void GetGeometryPointerPosition(void *, void *);
extern void GetGeometryPointerQuaternion(void *, void *);
extern void SetLayoutClassRootQuaternion(Chr *, float *);

static inline void quatYAxis(float *out, float *x)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vaddy.z vf6, vf0, vf7y\n"
        "vsubw.z vf6, vf6, vf7w\n"
        "vsubx.y vf6, vf0, vf5x\n"
        "vsubz.y vf6, vf6, vf5z\n"
        "vaddz.x vf6, vf7, vf7z\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.y vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        : : "r"(out), "r"(x) : "memory");
}

static inline void quatZAxis(float *out, float *x)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
        "vmul.xyzw vf5, vf4, vf4\n"
        "vmr32.xyzw vf6, vf4\n"
        "vmul.xyzw vf7, vf6, vf4\n"
        "vmr32.xyzw vf6, vf6\n"
        "vmul.xyzw vf8, vf6, vf4\n"
        "vsubx.z vf6, vf0, vf5x\n"
        "vsuby.z vf6, vf6, vf5y\n"
        "vaddw.y vf6, vf7, vf7w\n"
        "vsuby.x vf6, vf8, vf8y\n"
        "vsub.w vf6, vf0, vf0\n"
        "vadd.w vf5, vf0, vf0\n"
        "vmulw.xyz vf6, vf6, vf5w\n"
        "vaddw.z vf6, vf6, vf0w\n"
        "sqc2 vf6, 0x0(%0)\n"
        : : "r"(out), "r"(x) : "memory");
}

static inline void quatMul(float *out, float *x, float *y)
{
    float *p = x;
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
        : : "r"(out), "r"(p), "r"(y) : "memory");
}

static inline void quatNormalize(float *out, float *x)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
        "vmul.xyzw vf15, vf14, vf14\n"
        "vaddy.x vf15, vf15, vf15y\n"
        "vaddz.x vf15, vf15, vf15z\n"
        "vaddw.x vf15, vf15, vf15w\n"
        "vrsqrt Q, vf0w, vf15x\n"
        "vwaitq \n"
        "vmulq.xyzw vf15, vf14, Q\n"
        "sqc2 vf15, 0x0(%0)\n"
        : : "r"(out), "r"(x) : "memory");
}

static inline void quatPosToMatrix(float *out0, float *quat, float *pos)
{
    register float *out __asm__("$3") = out0;
    register float *pp __asm__("$4") = pos;
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(out), "r"(quat) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : "+r"(out) : "r"(pp) : "memory");
}

static inline void matInverse(float *dst, float *src)
{
    register float *dr __asm__("$2") = dst;
    register float *sr __asm__("$3") = src;
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dr), "r"(sr) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void matApply(float *out, float *m, float *v)
{
    register float *o5 __asm__("$5") = out;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                         : : "r"(v), "r"(m), "r"(o5) : "memory");
}

static inline void diffq(float *d, float *a, float *b, float *c)
{
    float *p = d;
    GetDifferencialQuaternionWithNoRegularize(p, a, b, c);
}

static inline void gpPos(float *d, void *g)
{
    float *p = d;
    GetGeometryPointerPosition(p, g);
}

static void func_0005DE30(void *o)
{
    Chr *c = GetCharacterClass();
    Vec4 q;
    Vec4 y;
    Vec4 z;
    Vec4 d;
    Vec4 m[4];
    Vec4 pos;
    Vec4 inv[4];

    if (c->f124 != 0) {
        float *cq = c->f13C;
        float *yu = YUnitVector;
        float *qp = q;
        float *v;
        float *dst;
        quatYAxis(y, cq);
        quatZAxis(z, cq);
        diffq(d, yu, y, z);
        quatMul(qp, d, cq);
        quatNormalize(qp, qp);
        {
            float *q2 = q;
            v = c->f134;
            gpPos(pos, c->gp);
            dst = c->f6D0;
            quatPosToMatrix((float *)m, q2, pos);
        }
        matInverse((float *)inv, (float *)m);
        matApply(dst, (float *)inv, v);
        SetLayoutClassRootQuaternion(c, q);
    }
    c->fA27 = 1;
    if (c->f124 != 0) {
        GetGeometryPointerPosition(c->f19C + 0x20, c->gp);
        GetGeometryPointerQuaternion(c->fA00, c->gp);
    }
}
