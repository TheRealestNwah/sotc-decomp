typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
#define VU_SUB_XYZ(dst, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n" \
                         "lqc2 vf06, 0(%2)\n" \
                         "vsub.xyz vf05, vf05, vf06\n" \
                         "sqc2 vf05, 0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

int GAMEUTIL_is_diff_nearly_equal_zero3D(float *a, float *b, float eps)
{
    Vec4 d;
    float *dp;
    VU_SUB_XYZ(&d, a, b);
    dp = d.f;
    if ((dp[0] < 0.0f ? -dp[0] : dp[0]) <= eps && (dp[1] < 0.0f ? -dp[1] : dp[1]) <= eps && (dp[2] < 0.0f ? -dp[2] : dp[2]) <= eps) return 1;
    return 0;
}
