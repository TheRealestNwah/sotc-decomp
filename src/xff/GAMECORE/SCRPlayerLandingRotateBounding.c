extern char IdentityQuaternion[], ZUnitVector[], YUnitVector[];
extern char *GetLayoutClass(void *);
extern int rand(void);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);

static inline void quatMul(float *d, void *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
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
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(d) : "memory");
}

static inline void vecCross(float *out, float *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline float fsqrt(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline void rotQuatZ(float *d, void *a, short ang)
{
    float r[4] __attribute__((aligned(16)));

    SetQuaternionByAxisRotateVWithNoRegularize(r, ang, ZUnitVector);
    quatMul(d, a, r);
}

void SCRPlayerLandingRotateBounding(void *obj)
{
    float tmp[4] __attribute__((aligned(16)));
    char *lc = GetLayoutClass(obj);
    short ang;

    ang = ((float)(rand() & 0xFFFF) / 32767.0f - 1.0f) * 8192.0f;
    rotQuatZ(tmp, IdentityQuaternion, -ang);
    quatMul(*(float **)(lc + 0x13C), tmp, *(float **)(lc + 0x13C));
    vecCross((float *)(*(char **)(lc + 0x19C) + 0x40), (float *)(lc + 0x30), YUnitVector);
    vecNormalize((float *)(*(char **)(lc + 0x19C) + 0x40));
    *(float *)(*(char **)(lc + 0x19C) + 0x50) = fsqrt(*(float *)(lc + 0x30) * *(float *)(lc + 0x30) + *(float *)(lc + 0x38) * *(float *)(lc + 0x38));
    *(float *)(lc + 0x34) *= -0.3f;
    *(float *)(lc + 0x30) *= 0.8f;
    *(float *)(lc + 0x38) *= 0.8f;
}
