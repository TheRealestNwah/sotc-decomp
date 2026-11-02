typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern Vec4 ZUnitVector, YUnitVector, YUnitVectorInv;
extern void SetQuaternionByCosineAxisRotateVWithNoRegularize(float *, float, Vec4 *);

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

static inline float dotXYZ(const float *a, const float *b)
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

void AI_GetYRotQuaternionFromVector(float *quaternion, Vec4 *vector)
{
    Vec4 dir;
    float cosine;

    dir.q = vector->q;
    dir.f[1] = 0.0f;
    normalizeXYZ(dir.f, dir.f);
    cosine = dotXYZ(dir.f, ZUnitVector.f);
    if (dir.f[0] <= 0.0f)
        SetQuaternionByCosineAxisRotateVWithNoRegularize(quaternion, cosine, &YUnitVector);
    else
        SetQuaternionByCosineAxisRotateVWithNoRegularize(quaternion, cosine, &YUnitVectorInv);
}
