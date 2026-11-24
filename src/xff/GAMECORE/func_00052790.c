/* Matched (150 words incl. the split tail func_00052A00). Path-follow step: scales o+0x140 by o+0x10C and gcGlobalVar.f190 into the move vector, accumulates it into a+0x50 and a+0x20, stores the speed (VU0 length via .word 0x4BA703BD) at a+0xC, clamps the distance to a+0x40 to o+0xF0, then (when the owner has a steering table) steers a+0x18/a+0x1C by AI_GetSideSignalFromDirLev and calls iosGetSinCosf. The mfc1 of each scale factor and the mtc1 of each VU0 length sit inside their asm blocks, which fixes the scheduling around them. The owner pointer and the first scale source are pinned to v0/v1 with local register variables, and an empty asm clobbering $3 before the gcGlobalVar scale moves the lui temp for &gcGlobalVar to v0 like the Original. */
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern struct {
    char pad[0x190];
    float f190;
} gcGlobalVar;
extern int AI_GetSideSignalFromDirLev(void *, void *);
extern void iosGetSinCosf(void *, float);

#define NORM(v)                                                 \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"                  \
                         "vmul.xyz vf7, vf5, vf5\n"             \
                         "vmulax.w ACC, vf0, vf7x\n"            \
                         "vmadday.w ACC, vf0, vf7y\n"           \
                         "vmaddz.w vf7, vf0, vf7z\n"            \
                         "vrsqrt Q, vf0w, vf7w\n"               \
                         "vwaitq\n"                             \
                         "vmulq.xyz vf5, vf5, Q\n"              \
                         "sqc2 vf5, 0x0(%0)\n"                  \
                         :                                      \
                         : "r"(v)                               \
                         : "memory")

static inline float vlen(void *v)
{
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf7, 0x0(%2)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         "mtc1 %0, %1\n"
                         : "=&r"(bits), "=f"(f)
                         : "r"(v)
                         : "memory");
    return f;
}

static inline float vdist(void *a, void *b)
{
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         "mtc1 %0, %1\n"
                         : "=&r"(bits), "=f"(f)
                         : "r"(a), "r"(b)
                         : "memory");
    return f;
}

#define SCALE(src, dst, f)                                      \
    __asm__ __volatile__("mfc1 $2, %1\n"                        \
                         "lqc2 vf5, 0x0(%0)\n"                  \
                         "qmtc2.ni $2, vf6\n"                   \
                         "vmulx.xyzw vf5, vf5, vf6x\n"          \
                         "sqc2 vf5, 0x0(%2)\n"                  \
                         :                                      \
                         : "r"(src), "f"(f), "r"(dst)           \
                         : "$2", "memory")

#define ADD3(a, b, d)                                           \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"                  \
                         "lqc2 vf6, 0x0(%1)\n"                  \
                         "vadd.xyz vf5, vf5, vf6\n"             \
                         "sqc2 vf5, 0x0(%2)\n"                  \
                         :                                      \
                         : "r"(a), "r"(b), "r"(d)               \
                         : "memory")

static void func_00052790(char *a)
{
    struct {
        Vec t0;
        Vec t1;
        Vec v;
        Vec t3;
        Vec dirA;
        Vec dirB;
    } L __attribute__((aligned(16)));
    char *p;
    float lim;
    float len;
    float d;
    float gf;
    float f3;
    float f12;
    float f4;
    float f1;
    float f0;
    float f20;

    {
        register char *o __asm__("$2") = *(char **)a;
        register char *src __asm__("$3") = o + 0x140;
        lim = *(float *)(o + 0xF0);
        SCALE(src, &L.v, *(float *)(o + 0x10C));
    }
    __asm__ __volatile__("" ::: "$3");
    SCALE(&L.v, &L.t0, gcGlobalVar.f190);
    ADD3(a + 0x50, &L.t0, a + 0x50);
    SCALE(a + 0x50, &L.t1, gcGlobalVar.f190);
    ADD3(a + 0x20, &L.t1, a + 0x20);
    *(float *)(a + 0xC) = vlen(a + 0x50);
    *(float *)(a + 8) = *(float *)(a + 8) + *(float *)(a + 0xC) * gcGlobalVar.f190;
    d = vdist(a + 0x20, a + 0x40);
    if (lim < d) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             :
                             : "r"(a + 0x20), "r"(a + 0x40), "r"(&L.t3)
                             : "memory");
        d = lim / vlen(&L.t3);
        SCALE(&L.t3, &L.t3, d);
        ADD3(a + 0x40, &L.t3, a + 0x20);
    }
    p = *(char **)a;
    if (*(int *)(*(char **)(p + 0x114) + 0x28) != 0) {
        L.dirA.q = *(s128 *)(p + 0x140);
        f20 = gcGlobalVar.f190;
        L.dirA.y = 0.0f;
        NORM(&L.dirA);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             :
                             : "r"(a + 0x50), "r"(&L.dirB)
                             : "memory");
        f1 = (float)AI_GetSideSignalFromDirLev(&L.dirB, &L.dirA);
        len = vlen(&L.v);
        {
            register char *oo __asm__("$3") = *(char **)a;
            char *t = *(char **)(oo + 0x114);
            f3 = *(float *)(a + 0x18);
            f3 = f3 + (-f3 * *(float *)(t + 0x1C) * f20 + f1 * *(float *)(t + 0x2C) * len * f20 / (*(float *)(a + 4) + 1.0f));
            *(float *)(a + 0x18) = f3;
            f12 = *(float *)(a + 0x1C) + f3 * f20;
            *(float *)(a + 0x1C) = f12;
        }
        iosGetSinCosf(a + 0x30, f12);
    }
}
