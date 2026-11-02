typedef float Vec4[4] __attribute__((aligned(16)));

typedef struct {
    char pad0[4];
    float scale;
    float limit;
} ChainParam;

typedef struct {
    char pad0[0x28];
    ChainParam *param;
} ChainDef;

typedef struct {
    char pad0[0x10];
    Vec4 *pos;
} ChainNode;

typedef struct {
    ChainDef *def;
    char pad4[0xC - 4];
    ChainNode *node;
} Chain;

static inline float diffRsqrt(float *out, float *a, float *b)
{
    float r;

    __asm__ __volatile__("lqc2 vf5, 0x0(%2)
"
                         "lqc2 vf6, 0x0(%3)
"
                         "vsub.xyzw vf8, vf5, vf6
"
                         "vmul.xyz vf7, vf8, vf8
"
                         "vaddy.x vf7, vf7, vf7y
"
                         "vaddz.x vf7, vf7, vf7z
"
                         "vrsqrt Q, vf0w, vf7x
"
                         "sqc2 vf8, 0x0(%1)
"
                         "vwaitq
"
                         "cfc2 $2, $vi22
"
                         "mtc1 $2, %0
"
                         : "=f"(r) : "r"(out), "r"(a), "r"(b) : "$2", "memory");
    return r;
}

static inline void addScaled(float *out, float *base, float *v, float s)
{
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)
"
                         "lqc2 vf5, 0x0(%2)
"
                         "mfc1 $8, %3
"
                         "qmtc2 $8, vf6
"
                         "vmulx.xyz vf5, vf5, vf6x
"
                         "vadd.xyz vf7, vf7, vf5
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(out), "r"(base), "r"(v), "f"(s) : "$8", "memory");
}

static inline void limitLength(float *p1, float *p0, float *d, float limit, float scale)
{
    float inv;

    inv = diffRsqrt(d, p1, p0);
    if (inv < limit)
        addScaled(p1, p0, d, scale * inv);
}

static inline void matApply(float *out, float *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline float fsqrt(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline float lenSqXY(float *v)
{
    float r;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xy vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "qmfc2 $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline void scaleXY(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "mfc1 $8, %1\n"
                         "qmtc2 $8, vf6\n"
                         "vmulx.xy vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "f"(s) : "$8", "memory");
}

static void func_00080960(Chain *c, char *lay)
{
    Vec4 t[3];
    float *p0, *p1;
    float limit, scale, d, inv;
    ChainParam *prm;

    prm = c->def->param;
    p0 = c->node->pos[0];
    p1 = c->node->pos[1];
    scale = prm->scale;
    limit = prm->limit;
    inv = diffRsqrt(t[0], p1, p0);
    if (inv < limit)
        addScaled(p1, p0, t[0], scale * inv);
    matApply(t[1], *(float **)(lay + 0x164), p1);
    d = lenSqXY(t[1]);
    if (d < 0.15f * 0.15f) {
        scaleXY(t[1], 0.15f / fsqrt(d));
        matApply(p1, *(float **)(lay + 0x158), t[1]);
        inv = diffRsqrt(t[2], p1, p0);
        if (inv < limit)
            addScaled(p1, p0, t[2], scale * inv);
    }
}
