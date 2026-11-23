/*
 * Parked attempt, 12 diffs, same size.
 *
 * Two place() calls (normalize, pick X/Y unit axis by F(o,0xC0), differential
 * quaternion, qmul, conjugate, rotate offset, add base) plus a final distance.
 * Remaining diffs are register choices only: the axis lq/sq temp is v0 where
 * the Original uses v1, and the rotate output / vadd re-load pointers swap
 * a0/v1/v0. Getting this close needed a rotate asm without a "memory" clobber
 * (so gcc recomputes sp+N) and an empty volatile asm after the axis copy (to
 * keep the sq out of the jal delay slot). The permuter found nothing better.
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

extern Vec4 XUnitVector, YUnitVector;
extern void GetDifferencialQuaternionWithNoRegularize(void *, void *, void *, void *);

#define F(p, o) (*(float *)((char *)(p) + (o)))

static inline void rotate(void *v, void *in, void *q)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%2)\n"
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
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(v), "r"(in), "r"(q));
}

static inline void normalize(void *v, void *in)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         : : "r"(in), "r"(v) : "memory");
}

static inline void qmul(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)
"
                         "lqc2 vf12, 0x0(%2)
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
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void qconj(void *out, void *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)
"
                         "vsubw.x vf5, vf0, vf0w
"
                         "vmulx.xyz vf11, vf11, vf5x
"
                         "sqc2 vf11, 0x0(%0)
"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void vadd3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vdist(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void place(char *o, char *dir, char *base, char *out, char *offs)
{
    Vec4 n;
    Vec4 off;
    Vec4 axis;
    Vec4 q;
    Vec4 qi;
    float f;
    Vec4 *ap;

    normalize(&n, dir);
    f = F(o, 0xC0);
    if (f < 0.0f) {
        if (-0.5f < f)
            ap = &XUnitVector;
        else
            ap = &YUnitVector;
    } else if (f < 0.5f)
        ap = &XUnitVector;
    else
        ap = &YUnitVector;
    axis.q = ap->q; __asm__ __volatile__("");
    GetDifferencialQuaternionWithNoRegularize(&q, &n, o + 0xC0, &axis);
    qmul(&q, &q, o + 0xA0);
    qconj(&qi, &q);
    rotate(&off, offs, &q);
    vadd3(out, base, &off);
    F(out, 0xC) = 1.0f;
}

static void func_00044D08(char *o, char *w)
{
    place(o, w + 0x90, w + 0x80, w + 0x220, w + 0x130);
    place(o, w + 0x90, w + 0x90, w + 0x230, w + 0x140);
    F(w, 0x244) = vdist(w + 0x220, w + 0x210);
}
#endif
