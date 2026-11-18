typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 XUnitVector, YUnitVector;
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

static inline float lengthXYZ(Vec4 *v)
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

static inline float distanceXYZ(Vec4 *a, Vec4 *b)
{
    float len;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(a), "r"(b) : "$2");
    return len;
}

static inline void scaleVector(Vec4 *out, Vec4 *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void setZero(Vec4 *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
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

static inline float fsqrt(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

#define MAX(a, b) ((b) < (a) ? (a) : (b))
#define MIN(a, b) ((b) < (a) ? (b) : (a))

int AI_CalcIntersectionCircleXZ(Vec4 *p1, Vec4 *p2, Vec4 *c1, Vec4 *c2, float r1, float r2)
{
    Vec4 v;
    Vec4 q;
    Vec4 iq;
    Vec4 dir;
    float d;
    float sum;
    float r1sq;
    float x;
    float z;

    d = distanceXYZ(c1, c2);
    setZero(p1);
    setZero(p2);
    sum = r1 + r2;
    if (sum == d || MAX(r1, r2) - MIN(r1, r2) == d) {
        subXYZ(&v, c2, c1);
        scaleVector(&v, &v, r1 / lengthXYZ(&v));
        addXYZ(p1, c1, &v);
        p1->f[3] = 1.0f;
        return 1;
    }
    if (d < sum && MAX(r1, r2) - MIN(r1, r2) < d) {
        subXYZ(&dir, c2, c1);
        scaleVector(&dir, &dir, 1.0f / d);
        GetDifferencialQuaternionWithNoRegularize(&q, &XUnitVector, &dir, &YUnitVector);
        conjugate(&iq, &q);
        r1sq = r1 * r1;
        x = (r1sq - r2 * r2 + d * d) / (d + d);
        p1->f[0] = x;
        p2->f[0] = x;
        z = fsqrt(r1sq - p1->f[0] * p1->f[0]);
        p1->f[2] = z;
        p2->f[2] = -z;
        quatRotateVector(p1, &iq, p1);
        quatRotateVector(p2, &iq, p2);
        addXYZ(p1, p1, c1);
        addXYZ(p2, p2, c1);
        p1->f[3] = 1.0f;
        p2->f[3] = 1.0f;
        return 2;
    }
    return 0;
}
