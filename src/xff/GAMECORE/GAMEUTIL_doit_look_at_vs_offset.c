extern void GAMEUTIL_doit_look_at_vs_offset_vec(void *, void *, float *, int, float *, int);

#define VU_SUB_XYZ(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "lqc2 vf06, 0(%2)\n" \
                         "vsub.xyz vf05, vf05, vf06\n" \
                         "sqc2 vf05, 0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

void GAMEUTIL_doit_look_at_vs_offset(void *c, float *base, void *b, float *p0, int d, float *p1, int e)
{
    float v0[4] __attribute__((aligned(16)));
    float v1[4] __attribute__((aligned(16)));
    VU_SUB_XYZ(v0, p0, base);
    VU_SUB_XYZ(v1, p1, base);
    GAMEUTIL_doit_look_at_vs_offset_vec(c, b, v0, d, v1, e);
}
