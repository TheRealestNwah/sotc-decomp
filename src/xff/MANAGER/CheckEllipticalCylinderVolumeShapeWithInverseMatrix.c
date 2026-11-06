typedef int s128 __attribute__((mode(TI)));

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(8))) Vec4;

static inline void applyMatrix(float *out, float *m, float *v)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline void scaleVector(float *out, float *a, void *b)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vmul.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float squareLength(float *v)
{
    float r;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf7, 0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         ".set reorder\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
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
extern float ZUnitVector[4];
extern float iosGetCosf(float);

static inline float squareLengthXZ(float *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0(%1)
"
                         "vmul.xz vf7, vf7, vf7
"
                         "vaddz.x vf7, vf7, vf7z
"
                         "qmfc2.ni $2, vf7
"
                         "mtc1 $2, %0
"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

int CheckEllipticalCylinderVolumeShapeWithInverseMatrix(float *inv, float *point, float *radius, float *shape)
{
    float local[4] __attribute__((aligned(16)));
    Vec4 scale __attribute__((aligned(16)));
    float sq;
    int result;
    float cone;
    float one;
    float y;

    {
        float one = 1.0f;
        Vec4 tmp;
        float x = one / radius[0];
        float yy = one / radius[1];
        float z = one / radius[2];
        tmp.w = 0.0f;
        tmp.x = x;
        tmp.z = z;
        tmp.y = yy;
        scale = tmp;
    }
    {
        float *p = local;
        applyMatrix(p, inv, point);
        scaleVector(p, p, (float *)&scale);
    }
    sq = squareLengthXZ(local);
    result = 0;
    cone = shape[1];
    one = 1.0f;
    if (sq <= one) {
        if (shape[1] * cone <= sq) {
            y = local[1];
            if (y < 0.0f ? y > -1.0f : y < 1.0f) {
                float c = iosGetCosf(shape[0] * 0.5f);
                *(s128 *)&scale = *(s128 *)local;
                scale.y = 0.0f;
                normalizeXYZ((float *)&scale, (float *)&scale);
                result = (c < vecDot((float *)&scale, (float *)&ZUnitVector)) != 0;
            }
        }
    }
    return result;
}
