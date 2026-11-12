typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int B_0018B804;
extern float B_0018B800;
extern char B_0018B7E0[];
extern char XUnitVector[], YUnitVector[], ZUnitVector[], ZUnitVectorInv[], IdentityQuaternion[];
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, void *, void *);

static inline void quatMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

#ifdef NONMATCHING /* 26 diffs, 150 vs 149 words: the pinned Identity pointer ($s4 here) costs one extra saved register; the original keeps it in $s0 and &q0 in $s2 */
void nico_player_colfit_SetLower(char *c)
{
    float q0[4] __attribute__((aligned(16)));
    float q1[4] __attribute__((aligned(16)));
    float q2[4] __attribute__((aligned(16)));
    float q3[4] __attribute__((aligned(16)));
    float q4[4] __attribute__((aligned(16)));
    float q5[4] __attribute__((aligned(16)));
    float q6[4] __attribute__((aligned(16)));
    char *bone;
    register char *iq __asm__("$20");
    register float *d0 __asm__("$16");

    if (B_0018B804 == 0)
        return;
    bone = *(char **)(*(char **)(c + 0x10) + 8) + (*(int *)(c + 0x14) << 6) + 0x20;
    iq = IdentityQuaternion;
    d0 = q0;
    SetQuaternionByAxisRotateVWithNoRegularize(q1, (short)(int)(B_0018B800 * 32768.0f / 3.1415927f), XUnitVector);
    quatMul(d0, iq, q1);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         : : "r"(B_0018B7E0), "r"(q3) : "memory");
    GetDifferencialQuaternionWithNoRegularize(q2, (float *)ZUnitVectorInv, q3, YUnitVector);
    quatMul(d0, d0, q2);
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(q5), "r"(bone) : "memory");
    quatMul(q5, q5, d0);
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(q6), "r"(q5) : "memory");
    GetDifferencialQuaternionWithNoRegularize(q4, q6, ZUnitVector, YUnitVector);
    quatMul(*(char **)(c + 4) + (*(int *)(c + 0x14) << 4), bone, q4);
}
#endif
