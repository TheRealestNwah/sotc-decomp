/* Clamps a vector's length into [min, 1] and its direction into a cone around +Z. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct F4 { float x, y, z; int w; } F4 __attribute__((aligned(8)));

extern char ZUnitVector[];
extern char YUnitVector[];
extern float iosGetCosf(float);
extern void SetQuaternionByAxisRotateV(void *, short, void *);

static inline void mulXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecLen(void *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

static inline void scaleXYZ(void *out, void *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline float dotXYZ(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}

static inline void normalize(void *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void outerXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatRotateVector(Vec4 *out0, void *quat0, void *vec0)
{
    register void *vec __asm__("$2") = vec0;
    register Vec4 *out __asm__("$3") = out0;
    register void *quat __asm__("$4") = quat0;
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

/* Parked: 7 diffs.
 * Remaining: the scheduling of the inverse scale vector's `w = 0` store (6 words,
 * the Original issues it after the first div.s, this C before the loads), and the
 * copy of n into t storing through the pointer register instead of 0x50($sp).
 */
#ifdef NONMATCHING
static float D_00136BD0[4] = { 0.0f, 0.0f, 1.0f, 0.0f };

static void func_00072B58(Vec4 *out, char *a1, Vec4 *in)
{
    Vec4 v;
    F4 inv;
    F4 n __attribute__((aligned(16)));
    Vec4 q;
    Vec4 axis;
    Vec4 t;
    float *scale = (float *)(a1 + 0x40);
    int changed = 0;
    float len;
    float c;
    float half;
    float lim;

    n.x = 1.0f / scale[0];
    n.y = 1.0f / scale[1];
    n.z = 1.0f / scale[2];
    n.w = 0;
    inv = n;
    mulXYZ(&v, in, &inv);
    len = vecLen(&v);
    scaleXYZ(&n, &v, 1.0f / len);
    if (1.0f <= len) {
        v.q = *(s128 *)&n;
        len = 1.0f;
        changed = 1;
    } else {
        lim = *(float *)(a1 + 0x58);
        if (len <= lim) {
            scaleXYZ(&v, &n, lim);
            len = lim;
            changed = 1;
        }
    }
    c = dotXYZ(&n, ZUnitVector);
    half = *(float *)(a1 + 0x54) * 0.5f;
    if (c < iosGetCosf(half)) {
        Vec4 *qp;
        short ang = (int)(half * 32768.0f / 3.1415927f);
        if (c <= -0.9999f) {
            qp = &q;
            SetQuaternionByAxisRotateV(qp, ang, YUnitVector);
        } else {
            Vec4 *tp = &t;
            tp->q = *(s128 *)&n;
            tp->f[2] = 0.0f;
            normalize(tp);
            outerXYZ(&axis, ZUnitVector, tp);
            qp = &q;
            SetQuaternionByAxisRotateV(qp, -ang, &axis);
        }
        D_00136BD0[2] = len;
        quatRotateVector(&v, qp, D_00136BD0);
        changed = 1;
    }
    if (changed) {
        mulXYZ(out, &v, scale);
        out->f[3] = 1.0f;
    } else {
        out->q = in->q;
    }
}
#endif
