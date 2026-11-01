extern void iosInverseMatrix(float *, float *);

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

static inline Vec4 makeVec(float x, float y, float z, float w)
{
    Vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

int CheckEllipticalSphereVolume(float *matrix, float *point, float *radius)
{
    float inv[16] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    Vec4 scale __attribute__((aligned(16)));

    iosInverseMatrix(inv, matrix);
    {
        float one = 1.0f;
        scale = makeVec(one / radius[0], one / radius[1], one / radius[2], 0.0f);
    }
    {
        float *p = local;
        applyMatrix(p, inv, point);
        scaleVector(p, p, &scale);
    }
    return squareLength(local) <= 1.0f;
}
