typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

#define I(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define Q(p, o) (*(s128 *)((char *)(p) + (o)))

extern Vec4 ZeroVector;
extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern float iosGetASinfExact(float);
extern void Kite_SetEventIDList(void *, int, int);
extern void AI_GetRandomCircleOfsXZ(Vec4 *, float, float);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, void *, int, int, void *, void *);
extern int AI_JudgeNotCharaObjFunc();
extern int AI_JudgeColAttrFunc();
extern void *GetGeometryPointerCollisionDB(void *);
extern float *GetCollisionDBPlane(void *);
extern void func_000A1DD0(void *, void *, void *);
extern void func_000A21B0(void *, void *, void *);
extern void func_000A2678(void *, void *);

typedef struct {
    Vec4 start;
    char pad10[0x30];
    Vec4 hit;
} ColResult;

static inline float lenXYZ(void *v)
{
    float len;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(v) : "$2");
    return len;
}

static inline void addXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalizeXYZ(void *out, void *in)
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
                         : : "r"(out), "r"(in) : "memory");
}

static inline void scaleVector(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void quatRotateVector(Vec4 *out, float *quat, Vec4 *vec)
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

static inline void randomAround(void *out, void *center, float rmin, float rmax)
{
    Vec4 ofs;

    AI_GetRandomCircleOfsXZ(&ofs, rmin, rmax);
    addXYZ(out, center, &ofs);
}

/* Parked: 2 words differ (sw $zero,0x798 and lq of the base vector swap
   around the else-branch `b`'s delay slot) */
#ifdef NONMATCHING
static void func_000A2F48(char *w)
{
    int i;
    int t;
    char *k;
    float len;
    ColResult res;
    Vec4 tmp;
    Vec4 pos;

    isysGetThisSubThread();
    if (I(w, 0x268) == I(w, 0x26C))
        return;
    I(w, 0x290) = 0;
    I(w, 0x2B8) = 0;
    I(w, 0x2C8) = 0;
    I(w, 0x320) = 0;
    I(w, 0x2E0) = 0;
    I(w, 0x300) = 0;
    switch (I(w, 0x26C)) {
    case 0:
        Q(w, 0x2E0) = ZeroVector.q;
        F(w, 0x28C) = 10.0f;
        F(w, 0x304) = 0.0f;
        F(w, 0x30C) = 1.0f;
        I(w, 0x318) = 0;
        I(w, 0x2FC) = 0;
        I(w, 0x2F8) = 0;
        I(w, 0x2F4) = 0;
        F(w, 0x314) = 1.0f;
        break;
    case 2:
        F(w, 0x30C) = 1.0f;
        F(w, 0x314) = 1.0f;
        I(w, 0x764) = 0;
        I(w, 0x318) = 0;
        I(w, 0x2FC) = 0;
        k = *(char **)(w + 0x20);
        F(w, 0x304) = iosGetASinfExact(F(k, 0xC4) / lenXYZ(k + 0xC0));
        Q(w, 0x2E0) = Q(*(char **)(w + 0x20), 0xC0);
        break;
    case 4:
        I(w, 0x584) = 1;
        F(w, 0x28C) = 0.0f;
        I(w, 0x300) = 0;
        if (I(w, 0) == 8)
            return;
        for (i = 0; i < 2; i++)
            Kite_SetEventIDList(w + 0x370, 1, i);
        break;
    case 5:
        F(w, 0x28C) = 5.0f;
        break;
    case 6:
        F(w, 0x28C) = 5.0f;
        break;
    case 7:
        F(w, 0x28C) = 5.0f;
        break;
    case 9:
        t = I(w, 0x274);
        if (t == 4 || t == 6 || t == 8) {
            char *dst = w + 0x770;
            char *base = w + 0x590;
            Vec4 *pp = &pos;
            float r = F(*(char **)(w + 0x20), 0xE8) * 0.9f;

            randomAround(pp, base, r * 0.19999999f, r);
            tmp.q = pos.q;
            tmp.f[1] -= 2.0f;
            pos.f[1] += 2.0f;
            if (ClipCollisionDirectCallBack(&res, pp, &tmp, gcGlobalVar + 0x230, AI_JudgeNotCharaObjFunc, 0, 0,
                                            AI_JudgeColAttrFunc, 0) != 0) {
                if (GetCollisionDBPlane(GetGeometryPointerCollisionDB(&res))[1] > 0.785398126f) {
                    I(w, 0x798) = 1;
                    Q(dst, 0) = res.hit.q;
                } else {
                    I(w, 0x798) = 0;
                    Q(dst, 0) = Q(base, 0);
                }
            } else {
                I(w, 0x798) = 0;
                pos.f[1] = F(base, 4);
                Q(dst, 0) = pos.q;
            }
            I(w, 0x764) = 1;
        } else if (t == 5) {
            char *dst = w + 0x770;
            char *base = w + 0x590;

            AI_GetRandomCircleOfsXZ(&res.start, 1.0f, F(*(char **)(w + 0x20), 0xE8) * 0.9f);
            addXYZ(dst, base, &res.start);
            I(w, 0x764) = 1;
        } else {
            I(w, 0x764) = 0;
        }
        break;
    case 0xE:
        func_000A1DD0(w, w + 0xB0, w + 0x6B0);
        func_000A2678(w, w + 0x6B0);
        F(w, 0x28C) = F(w, 0x740);
        break;
    case 0xF:
        func_000A21B0(w, w + 0xB0, w + 0x6B0);
        func_000A2678(w, w + 0x6B0);
        break;
    case 0x10:
        len = lenXYZ(w + 0x730);
        I(w, 0x764) = 0;
        quatRotateVector((Vec4 *)(w + 0x2E0), (float *)(w + 0x250), (Vec4 *)(w + 0x730));
        I(w, 0x2E0) = 0;
        normalizeXYZ(w + 0x2E0, w + 0x2E0);
        scaleVector(w + 0x2E0, w + 0x2E0, len);
        I(w, 0x2F8) = 0;
        I(w, 0x2F4) = 0;
        break;
    case 0x14:
        F(w, 0x28C) = 10.0f;
        break;
    }
}
#endif
