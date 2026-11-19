typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[8];
    float x8;
    char padC[0x10];
    float x1C, x20, x24, x28, x2C;
    char pad30[0x10];
    float x40, x44, x48;
} KiteParam;

extern Vec4 ZeroVector, ZUnitVector;
extern char *GetLayoutClass(int);
extern int AI_UpdateVelocity(float *, float, float);

static inline void scaleXZ(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "mfc1 $8, %2\n"
                         "qmtc2.ni $8, vf6\n"
                         "vmulx.xz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "f"(s) : "$8", "memory");
}

static inline void normalizeXYZ(float *output, const float *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
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

static inline float lerpf(float x, float x0, float x1, float y0, float y1)
{
    return (x - x0) * (y1 - y0) / (x1 - x0) + y0;
}


/* Parked: 7 words differ with -fno-gcse (register allocation); permuter made no progress in 630 iterations */
#ifdef NONMATCHING
static void func_000AB478(char *w)
{
    Vec4 v;
    float d, t, f;
    KiteParam *p;

    if (*(int *)(w + 0x2C) != 0) {
        *(s128 *)(w + 0x300) = ZeroVector.q;
        return;
    }
    p = *(KiteParam **)(w + 0x34);
    if (p->x8 < *(float *)(w + 0x1A4)) {
        float mid, cur, lo, hi, num, den;
        d = *(float *)(w + 0x1A4) - p->x8;
        if (d > 5.0f) d = 5.0f;
        mid = (p->x1C - p->x20) * (p->x2C - p->x28) / (p->x24 - p->x20) + p->x28;
        cur = *(float *)(w + 0x2CC);
        t = cur <= mid ? lerpf(cur, p->x28, mid, p->x40, p->x44) : lerpf(cur, mid, p->x2C, p->x44, p->x48);
        if (t < p->x40) t = p->x40;
        if (p->x48 < t) t = p->x48;
        *(float *)(w + 0x2D8) = t;
        scaleXZ((float *)(w + 0x300), (float *)(w + 0x190), d);
        scaleXZ((float *)(w + 0x300), (float *)(w + 0x300), *(float *)(w + 0x2D8));
        f = (1.0f - (*(float *)(w + 0x1B0) + 1.0f) * 0.25f) * d * 3.0f * *(float *)(w + 0x2D8);
        quatRotateVector(&v, *(float **)(GetLayoutClass(*(int *)(w + 0x28)) + 0x13C), &ZUnitVector);
        v.f[1] = 0.0f;
        normalizeXYZ(v.f, v.f);
        quatRotateVector(&v, (float *)(w + 0x2B0), &v);
        t = 1.0f - (v.f[2] + 1.0f) * 0.5f;
        if (v.f[0] > 0.0f) t = -t;
        *(float *)(w + 0x2C0) = t * f;
    } else {
        AI_UpdateVelocity((float *)(w + 0x2C0), 0.0f, 0.5f);
        AI_UpdateVelocity((float *)(w + 0x300), 0.0f, 0.5f);
        AI_UpdateVelocity((float *)(w + 0x304), 0.0f, 0.5f);
        AI_UpdateVelocity((float *)(w + 0x308), 0.0f, 0.5f);
    }
}
#endif
