#ifdef NONMATCHING /* parked draft: 47 diffs; FABS macro form fits, prologue order (lq before addiu sp, mov.s f2) and one extra addiu differ */
typedef int s128 __attribute__((mode(TI)));

extern float iosGetATan2fExact(float, float);
#define FABS(x) ((x) < 0.0f ? -(x) : (x))

void func_0004BC58(float *out0, float *out1, float *src)
{
    float w[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    float *pv;

    *(s128 *)v = *(s128 *)src;
    *(s128 *)w = *(s128 *)src;
    if (FABS(v[1]) - 1.0f < 0.0f ? FABS(v[1]) - 1.0f < -0.001f : FABS(v[1]) - 1.0f > 0.001f) {
        v[1] = 0.0f;
        __asm__ __volatile__("addiu %0, $29, 0x10" : "=r"(pv));
        __asm__ __volatile__("addiu %0, $29, 0x10" : "=r"(pv));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                             : : "r"(pv) : "memory");
        *out0 = iosGetATan2fExact(v[0], v[2]) * 57.29578f;
    }
    if (FABS(w[0]) - 1.0f < 0.0f ? FABS(w[0]) - 1.0f < -0.001f : FABS(w[0]) - 1.0f > 0.001f) {
        w[0] = 0.0f;
        __asm__ __volatile__("addiu %0, $29, 0x10" : "=r"(pv));
    __asm__ __volatile__("lqc2 vf5, 0x0($29)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                             : : : "memory");
        __asm__ __volatile__("sqc2 vf5, 0x0($29)" : : : "memory");
        *out1 = iosGetATan2fExact(w[1], w[2]) * 57.29578f;
    }
}
#endif
