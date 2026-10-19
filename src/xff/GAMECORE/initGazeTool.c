typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void *iosgluGetCameraContext(void);
extern Vec4 B_001A5A50;
extern char D_0017B840[];
extern void createParamMenu(char *, int);
extern void cursorLockParamMenu(char *, int);

static inline void scale(Vec4 *o, Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(v), "r"(s) : "memory");
}

static inline void add(Vec4 *o, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vadd.xyz vf05, vf05, vf06\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(a), "r"(b) : "memory");
}

void initGazeTool(void)
{
    char *c = iosgluGetCameraContext();
    scale(&B_001A5A50, (Vec4 *)(c + 0x150), 15.0f);
    add(&B_001A5A50, (Vec4 *)(c + 0x140), &B_001A5A50);
    B_001A5A50.f[3] = 1.0f;
    createParamMenu(D_0017B840, 0);
    cursorLockParamMenu(D_0017B840, 1);
    c = 0;
}
