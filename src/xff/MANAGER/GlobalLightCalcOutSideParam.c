typedef float Vector[4] __attribute__((aligned(16)));

typedef struct {
    char p0[0xE0];
    Vector center;
    Vector extent;
    char p100[0x18];
    float outRadius;
    char p11C[0x18];
    float outDistance;
} GlobalLightWork;

static inline float squareLengthXYZ(float *a)
{
    float result;
    __asm__ __volatile__(
        "lqc2 vf7, 0(%1)\n" "vmul.xyz vf7, vf7, vf7\n"
        "vaddy.x vf7, vf7, vf7y\n" "vaddz.x vf7, vf7, vf7z\n"
        "qmfc2.ni $2, vf7\n" "mtc1 $2, %0\n"
        : "=f"(result) : "r"(a) : "$2");
    return result;
}

static inline void subXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__(
        "lqc2 vf5, 0(%1)\n" "lqc2 vf6, 0(%2)\n"
        "vsub.xyz vf5, vf5, vf6\n" "sqc2 vf5, 0(%0)\n"
        : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float sqrtF(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

float GlobalLightCalcOutSideParam(GlobalLightWork *w)
{
    Vector v;
    Vector d;
    float m;

    m = w->extent[0];
    if (m < w->extent[1]) {
        m = w->extent[1];
    }
    if (m < w->extent[2]) {
        m = w->extent[2];
    }
    v[0] = m;
    v[1] = m;
    v[2] = m;
    m = squareLengthXYZ(v);
    subXYZ(d, w->extent, w->center);
    subXYZ(v, v, d);
    w->outDistance = sqrtF(squareLengthXYZ(w->extent));
    w->outRadius = m;
    return m;
}
