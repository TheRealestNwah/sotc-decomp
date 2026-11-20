typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 YUnitVector;
extern void GetDifferencialQuaternionWithNoRegularize(Vec4 *, Vec4 *, Vec4 *, Vec4 *);

static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalize(Vec4 *v0, Vec4 *v1)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v0), "r"(v1) : "memory");
}

static inline void conjugate(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void quatRotateVector(Vec4 *out, Vec4 *quat, Vec4 *vec)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

static inline void quatRotateVectorV1(Vec4 *out, Vec4 *quat0, Vec4 *vec)
{
    register Vec4 *quat __asm__("$3") = quat0;

    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}

extern Vec4 ZUnitVector;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern int AI_CheckNormZero(Vec4 *);

static void func_000A1AC0(char *obj, Vec4 *out, Vec4 *add, float h)
{
    Vec4 b;
    Vec4 a;
    Vec4 dir;
    Vec4 tmp;
    Vec4 q;
    Vec4 iq;
    char *lay;

    lay = GetLayoutClass(isysGetThisSubThread());
    subXYZ(&a, (Vec4 *)(obj + 0x600), (Vec4 *)(obj + 0x680));
    subXYZ(&b, *(Vec4 **)(lay + 0x134), (Vec4 *)(obj + 0x680));
    if (AI_CheckNormZero(&a) != 0) {
        normalize(&dir, &a);
    } else {
        addXYZ(out, (Vec4 *)(obj + 0x600), add);
        return;
    }
    GetDifferencialQuaternionWithNoRegularize(&q, &ZUnitVector, &dir, &YUnitVector);
    conjugate(&iq, &q);
    quatRotateVectorV1(&a, &q, &a);
    quatRotateVector(&b, &q, &b);
    {
        float z = 0.0f;

        /* the Original sets up the 0.0f before loading b.f[2] */
        __asm__ __volatile__("" : "+f"(z));
        tmp.q = add->q;
        if (z < b.f[2])
            tmp.f[2] += b.f[2] + h;
        else
            tmp.f[2] += h;
    }
    if (tmp.f[2] > a.f[2])
        tmp.f[2] = a.f[2] + add->f[2];
    tmp.f[3] = 1.0f;
    quatRotateVector(&tmp, &iq, &tmp);
    addXYZ(&tmp, &tmp, (Vec4 *)(obj + 0x680));
    out->q = tmp.q;
}
