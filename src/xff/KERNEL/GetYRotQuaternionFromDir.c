typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 YUnitVector;
extern Vec4 YUnitVectorInv;
#define VU_SCALE_XYZW(dst, src, scale) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "qmtc2 %2, vf06\n" \
                         "vmulx.xyzw vf05, vf05, vf06x\n" \
                         "sqc2 vf05, 0x0(%0)\n" \
                         : : "r"(dst), "r"(src), "r"(scale) : "memory")

static inline float sqrtF(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

/* Same body as SetQuaternionByCosineAxisRotateVWithNoRegularize, inlined. */
static inline void quat_from_cosine_axis(float *q, float *axis, float c)
{
    float w = sqrtF((c + 1.0f) * 0.5f);
    float s = sqrtF((1.0f - c) * 0.5f);
    VU_SCALE_XYZW(q, axis, s);
    q[3] = w;
}

void GetYRotQuaternionFromDir(float *q, float *dir)
{
    float *axis;
    if (dir[0] < 0.0f) axis = YUnitVector.f;
    else axis = YUnitVectorInv.f;
    quat_from_cosine_axis(q, axis, dir[2]);
}
