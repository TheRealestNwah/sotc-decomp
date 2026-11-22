/*
 * func_00032188: samples a quaternion track at a frame (wraps the frame,
 * then returns the key or a hemisphere-corrected lerp of the two nearest
 * keys).
 *
 * Parked: 8 diffs (ee-gcc 2.96 -O2 -G0).
 * Remaining: the else path of the wrap computes n - 1 into $v1 instead of
 * $v0 (3 words), and the two getKey version tests use bnel with the zero
 * result in the delay slot where the original uses bnez and shares an
 * earlier return-zero (5 words, including the shifted beql targets).
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    short ver;
    char pad2[2];
    short count;
    char pad6[0x1A];
    void *p20;
    void *p24;
} Track;

extern void func_00031438(Vec4 *, void *, void *, int);

static inline int getKey(Vec4 *o, Track *t, int k)
{
    if (t->ver >= 4 && t->p24 != 0) {
        func_00031438(o, t->p20, t->p24, k);
        return 1;
    }
    return 0;
}

static inline float dot4(Vec4 *a, Vec4 *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
        "lqc2 vf15, 0x0(%2)\n"
        "vmul.xyzw vf15, vf14, vf15\n"
        "vaddy.x vf15, vf15, vf15y\n"
        "vaddz.x vf15, vf15, vf15z\n"
        "vaddw.x vf15, vf15, vf15w\n"
        "qmfc2.ni $2, vf15\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void scale4(Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
        "qmtc2.ni %1, vf6\n"
        "vmulx.xyzw vf5, vf5, vf6x\n"
        "sqc2 vf5, 0x0(%0)\n"
        : : "r"(v), "r"(s) : "memory");
}

static inline void lerp4(Vec4 *out, Vec4 *a, Vec4 *b, float w)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
        "qmtc2.ni $8, vf7\n"
        "lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vsubx.w vf8, vf0, vf7x\n"
        "vmulax.xyzw ACC, vf5, vf7x\n"
        "vmaddw.xyzw vf9, vf6, vf8w\n"
        "sqc2 vf9, 0x0(%0)\n"
        : : "r"(out), "r"(a), "r"(b), "f"(w) : "$8", "memory");
}

static inline void nearest(Vec4 *out, Vec4 *a, Vec4 *b, Vec4 *c, float w)
{
    int d;

    c->q = b->q;
    *(float *)&d = dot4(a, c);
    if (d < 0)
        scale4(c, -1.0f);
    lerp4(out, a, c, w);
}

static int func_00032188(Vec4 *out, Track *t, float frame)
{
    Vec4 a, b, c;
    float orig = frame;
    int n = t->count;
    int i, k, k1;
    float f, s;

    if (n == 1) {
        frame = frame - (float)(int)frame;
    } else {
        int m = n - 1;
        frame = frame - (float)((int)(frame / (float)m) * m);
    }
    if (frame == 0.0f && 0.0f < orig)
        frame = (float)(t->count - 1);
    f = frame;
    k = (int)f;
    k1 = k + 1;
    s = f - (float)k;
    if (s == 0.0f)
        return getKey(out, t, k);
    if (s < 0.5f) {
        if (!getKey(&a, t, k))
            return 0;
        getKey(&b, t, k1);
        nearest(out, &a, &b, &c, 1.0f - s);
    } else {
        if (!getKey(&a, t, k))
            return 0;
        getKey(&b, t, k1);
        nearest(out, &b, &a, &c, s);
    }
    return 1;
}
#endif
