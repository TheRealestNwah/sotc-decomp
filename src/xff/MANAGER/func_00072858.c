typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;
typedef union { s128 q; float f[4]; } QVec;

extern void iosAbsVector(void *, void *);
extern void iosGetScaleInverseVector(void *, void *);
extern float iosGetCosf(float);
extern float iosGetSinf(float);
extern float ZeroVector[4];
extern float ZUnitVector[4];
extern void *memset(void *, int, unsigned int);

#define VOP3(op, d, a, b) __asm__ __volatile__(".set noreorder\n" \
    "lqc2 vf5, 0x0(%1)\n" "lqc2 vf6, 0x0(%2)\n" op " vf5, vf5, vf6\n" "sqc2 vf5, 0x0(%0)\n" ".set reorder\n" \
    : : "r"(d), "r"(a), "r"(b) : "memory")

static inline void lerpXYZ(float *d, float *a, float *b, float t)
{
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(d), "r"(a), "r"(b), "f"(t) : "memory", "$8");
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

static inline float lengthXYZ(float *v)
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

static inline void scaleX(float *d, float *a, float s)
{
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $2, %2\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(d), "r"(a), "f"(s) : "memory", "$2");
}

static inline float vecDot(float *a, float *b)
{
    float dot;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

typedef struct {
    char pad0[0x40];
    Vec4 size;
    char pad50[4];
    float angle;
    float radius;
} Shape;

static void func_00072858(float *out, Shape *sh, float *pos)
{
    Vec4 base = { 0.0f, 0.0f, (sh->radius + 1.0f) * 0.5f };
    Vec4 abs;
    Vec4 inv;
    Vec4 n;
    QVec dir;
    float t;
    float len;
    float half;
    float c;
    float d;
    float one;
    float r;

    iosAbsVector(&abs, &sh->size);
    if (abs.x < 0.001f || abs.z < 0.001f || abs.y < 0.001f) {
        VOP3("vmul.xyz", out, &base, &abs);
    }
    iosGetScaleInverseVector(&inv, &abs);
    VOP3("vmul.xyz", out, pos, &inv);
    VOP3("vsub.xyz", out, out, &base);
    one = 1.0f;
    t = out[1];
    if (t < 0.0f) t = -t;
    if (0.001f < t) {
        float u = one / t;
        if (u < one) {
            lerpXYZ(out, out, ZeroVector, u);
        }
    }
    VOP3("vadd.xyz", out, out, &base);
    dir.q = *(s128 *)out;
    dir.f[1] = 0.0f;
    normalizeXYZ((float *)&n, dir.f);
    len = lengthXYZ(dir.f);
    r = sh->radius;
    if (1.0f < len) {
        dir.q = *(s128 *)&n;
        len = 1.0f;
    } else if (len < r) {
        scaleX(dir.f, (float *)&n, r);
        len = r;
    }
    d = vecDot((float *)&n, ZUnitVector);
    half = sh->angle * 0.5f;
    c = iosGetCosf(half);
    if (d < c) {
        float s = iosGetSinf(half);
        dir.f[0] = (dir.f[0] < 0.0f ? -len : len) * s;
        dir.f[2] = len * c;
    }
    out[0] = dir.f[0];
    out[2] = dir.f[2];
    VOP3("vmul.xyz", out, out, &abs);
}
