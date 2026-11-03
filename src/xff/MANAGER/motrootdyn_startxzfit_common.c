#ifdef NONMATCHING /* 15 diffs: register choice for the quaternion-multiply operands and scheduling of the ZeroVector store */
typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(8))) F4;
typedef union { s128 q; F4 f; } Vec4;

extern int DldSysUndefSymbol;
extern s128 ZeroVector;
extern void UnlinkSecureParentInfo(void *);

static inline void *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    unsigned int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != (int *)DldSysUndefSymbol)
        return (void *)(t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3]);
    return 0;
}

static inline void quatMul(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                         "lqc2 vf12, 0(%2)\n"
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
                         "sqc2 vf13, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void zeroVector(void *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

void motrootdyn_startxzfit_common(void *motion, char *c)
{
    char *e;

    quatMul(c + 0x470, *(void **)(c + 0x13C), c + 0x490);
    *(s128 *)(c + 0xAB0) = ZeroVector;
    e = dldElem((unsigned int *)(*(char **)(c + 0x1C0) + 0xC));
    if (e != 0 && (*(unsigned int *)(e + 0x14) >> 1) & 1) {
        Vec4 v;
        F4 f;
        f.x = *(float *)(e + 0x18);
        f.y = *(float *)(e + 0x1C);
        f.z = *(float *)(e + 0x20);
        f.w = *(float *)(e + 0x24);
        v.f = f;
        ((Vec4 *)(c + 0xB40))->q = v.q;
    } else {
        zeroVector(c + 0xB40);
    }
    *(int *)(c + 0xB50) = 0;
    UnlinkSecureParentInfo(c + 0xAC0);
    zeroVector(c + 0xB30);
}
#endif
