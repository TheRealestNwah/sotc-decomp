typedef int s128 __attribute__((mode(TI)));

extern s128 ZUnitVector;
extern float iosGetACosfExact(float x);

static inline float squareLength(void *v)
{
    float r;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         ".set reorder\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

float GetQuaternionAxisRotInfo(s128 *axis, float *q)
{
    if (squareLength(q) == 0.0f) {
        *axis = ZUnitVector;
        return 0.0f;
    }
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
                         : : "r"(axis), "r"(q) : "memory");
    return iosGetACosfExact(q[3]) * 2.0f;
}
