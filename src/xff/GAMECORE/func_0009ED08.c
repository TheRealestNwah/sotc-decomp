typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern char XUnitVector[], YUnitVector[], ZUnitVector[];
extern char *GetLayoutClass(int);
extern void *isysGetThisSubThread(void);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern void AI_GetYRotQuaternion(float *, float *);

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

static int func_0009ED08(float a, float c, float b)
{
    float q0[4] __attribute__((aligned(16)));
    float q1[4] __attribute__((aligned(16)));
    float q2[4] __attribute__((aligned(16)));
    float q3[4] __attribute__((aligned(16)));
    float q4[4] __attribute__((aligned(16)));
    char *lay = GetLayoutClass((int)isysGetThisSubThread());

    a *= 90.0f;
    a *= *(float *)(gcGlobalVar + 0x190);
    if (a < 0.0f ? a < -170.0f : a > 170.0f)
        a = a < 0.0f ? -170.0f : 170.0f;
    SetQuaternionByAxisRotateVWithNoRegularize(q0, (short)(int)(a * 32768.0f / 180.0f), YUnitVector);
    SetQuaternionByAxisRotateVWithNoRegularize(q1, (short)(int)(b * 32768.0f / 3.1415927f), ZUnitVector);
    quatMul(q2, q0, *(void **)(lay + 0x13C));
    AI_GetYRotQuaternion(q3, q2);
    if (c != 0.0f) {
        SetQuaternionByAxisRotateVWithNoRegularize(q4, (short)(int)(c * 32768.0f / 3.1415927f), XUnitVector);
        quatMul(q2, q4, q1);
    } else {
        *(s128 *)q2 = *(s128 *)q1;
    }
    quatMul(q2, q3, q2);
    **(s128 **)(lay + 0x13C) = *(s128 *)q2;
    return 1;
}
