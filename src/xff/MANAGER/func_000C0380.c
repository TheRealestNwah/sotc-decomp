typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int strcmp(const char *, const char *);
extern char *iosgluGetCameraContext(void);
extern float *D_001370D8;
extern float B_001499C8[], B_001499D8[], B_001499E8[];
extern int func_000C5E00(char *);
extern void func_000BFC68(char *, char *, int);
extern void func_000C5E40(char *, char *);
extern void func_000C5EC0(char *, char *);
extern void func_000C5FA0(char *, char *, char *);
extern void get_particle_parameter_blend_doit(void *, char *, int, int, float);
extern int func_000C0698(char *, char *, char *, void *, int);

static inline float distanceXYZ(void *a, void *b)
{
    float len;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(a), "r"(b) : "$2");
    return len;
}

static inline void subXYZ(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b));
}

static inline float dotXYZ(void *a, void *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

static int func_000C0380(char *e, char *p, int arg)
{
    char blend[0x160];
    Vec4 d;
    Vec4 *dp;
    char *s;
    int flag;

    if (e != 0) {
    flag = 1;
    if (strcmp(*(char **)(*(char **)(p + 0xD8) + 0x24), "PAUSE_START") == 0 ||
        strcmp(*(char **)(*(char **)(p + 0xD8) + 0x24), "PAUSE_END") == 0) {
        D_001370D8 = B_001499E8;
    } else if (func_000C5E00(p) == flag) {
        D_001370D8 = B_001499D8;
    } else {
        D_001370D8 = B_001499C8;
    }
    *(int *)(e + 0x198) = 0;
    func_000BFC68(e, p, 0);
    *(float *)(e + 0x130) = distanceXYZ(e + 0x10, iosgluGetCameraContext() + 0x140);
    {
        char *c = iosgluGetCameraContext();
        dp = &d;
        subXYZ(dp, e + 0x10, c + 0x140);
    }
    *(float *)(e + 0x134) = ABS(dotXYZ(dp, iosgluGetCameraContext() + 0x150));
    func_000C5E40(e, p);
    func_000C5EC0(e, p);
    s = *(char **)(p + 0xD4) + *(int *)(e + 0x118) * 0x1BC;
    if (*(int *)(p + 0xCC) == 1) {
        switch (*(unsigned int *)(s + 0x15C)) {
        case 1:
            *(float *)(e + 0x150) = *(float *)(s + 0xB4);
            break;
        case 0:
            *(float *)(e + 0x150) = 10000000.0f;
            break;
        case 2:
            *(float *)(e + 0x150) = *(float *)(s + 0xB4) + *(float *)(e + 0x14);
            break;
        default:
            *(float *)(e + 0x150) = *(float *)(s + 0xB4) + *(float *)(e + 0x14C);
            break;
        }
        switch (*(unsigned int *)(s + 0x160)) {
        case 1:
            *(float *)(e + 0x154) = *(float *)(s + 0x140);
            break;
        case 0:
            *(float *)(e + 0x154) = -10000000.0f;
            break;
        case 2:
            *(float *)(e + 0x154) = *(float *)(s + 0x140) + *(float *)(e + 0x14);
            break;
        default:
            *(float *)(e + 0x154) = *(float *)(s + 0x140) + *(float *)(e + 0x14C);
            break;
        }
    }
    flag = *(int *)(e + 0x168) != 0;
    func_000C5FA0(e, p, s);
    get_particle_parameter_blend_doit(blend, p, arg, *(int *)(e + 0x118), *(float *)(e + 0x16C));
    return func_000C0698(e, p, s, blend, flag);
    }
    return 0;
}
