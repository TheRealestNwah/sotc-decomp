typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern float gcGlobalVar[];
extern char YUnitVector[];
extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *, short, void *);

static inline void quatMul(void *out, void *a, void *b)
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
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatConj(void *out, void *in)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(in) : "memory");
}

static int func_000B76A8(char *w, float a, float b)
{
    Vec4 ry;
    Vec4 tmp;
    char *lc = GetLayoutClass(isysGetThisSubThread());
    float ang;

    ang = a * *(float *)(*(char **)(w + 0x64) + 0x10) * gcGlobalVar[0x190 / 4];
    if (ang < 0.0f ? ang < -170.0f : ang > 170.0f) {
        ang = ang < 0.0f ? -170.0f : 170.0f;
    }
    SetQuaternionByAxisRotateVWithNoRegularize(w + 0x280, (int)(b * 32768.0f / 3.1415926f), w + 0x270);
    SetQuaternionByAxisRotateVWithNoRegularize(&ry, (int)(ang * 32768.0f / 180.0f), YUnitVector);
    tmp.q = **(s128 **)(lc + 0x13C);
    quatMul(&tmp, w + 0x290, &tmp);
    quatMul(&tmp, &tmp, &ry);
    quatMul(*(void **)(lc + 0x13C), w + 0x280, &tmp);
    quatConj(w + 0x290, w + 0x280);
    return 0;
}
