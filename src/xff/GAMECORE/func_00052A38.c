/* Parked: 185 diffs, same size (166 words incl. the split tail func_00052CE0). Path-follow per-frame update (sibling of func_00052790 and func_000523E8): zeroes the move accumulator at owner+0x140, then adds a weighted pull toward each of the owner's waypoints (VU0 length through .word 0x4BA703BD, AI_GetInterRatioOutCut weight), the damped -o+0x108 * a+0x50 term, and a random jitter along the normalised offset to a+0x40 when iosGetRandom is below 0.1 * o+0x110; calls func_00052790, then func_00052558 when the speed bound at o+0x114 is exceeded, and finally adds gcGlobalVar.f190 to a+0x74. The second AI_GetInterRatioOutCut call passes only four floats, so it goes through an asm-renamed four-argument prototype. Remaining: the compiler hoists the zero/one constants and the loop-invariant pointers (a+0x20, &t1) into extra saved registers, which the Original does not. */
#ifdef NONMATCHING
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
extern float iosGetRandom(void);
extern float AI_GetInterRatioOutCut(float, float, float, float, float);
extern float AI_GetInterRatioOutCut4(float, float, float, float) __asm__("AI_GetInterRatioOutCut");
extern void func_000523E8(char *);
extern void func_00052790(char *);
extern void func_00052558(char *);

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

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         : "=&r"(bits)
                         : "r"(v)
                         : "memory");
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(bits));
    return f;
}

static inline float vdist(void *a, void *b)
{
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         : "=&r"(bits)
                         : "r"(a), "r"(b)
                         : "memory");
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(bits));
    return f;
}

#define SCALE(src, dst, f)                                      \
    do {                                                        \
        int bits_;                                              \
        __asm__("mfc1 %0, %1" : "=r"(bits_) : "f"(f));          \
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"              \
                             "qmtc2.ni %1, vf6\n"               \
                             "vmulx.xyzw vf5, vf5, vf6x\n"      \
                             "sqc2 vf5, 0x0(%2)\n"              \
                             :                                  \
                             : "r"(src), "r"(bits_), "r"(dst)   \
                             : "memory");                       \
    } while (0)

#define ADD3(a, b, d)                                           \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"                  \
                         "lqc2 vf6, 0x0(%1)\n"                  \
                         "vadd.xyz vf5, vf5, vf6\n"             \
                         "sqc2 vf5, 0x0(%2)\n"                  \
                         :                                      \
                         : "r"(a), "r"(b), "r"(d)               \
                         : "memory")

static void func_00052A38(char *a)
{
    struct {
        Vec t0;
        Vec t1;
        Vec t2;
        Vec t3;
        Vec t4;
    } L __attribute__((aligned(16)));
    char *o;
    char *p;
    int n;
    float len;
    float ratio;
    float k;
    float lim;
    float rnd;
    char *s2;
    char *s0;

    o = *(char **)a;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)
" : : "r"(o + 0x140) : "memory");
    func_000523E8(a);
    o = *(char **)a;
    n = *(int *)o;
    p = o + 0x10;
    if (n > 0) {
        do {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                                 "lqc2 vf6, 0x0(%1)
"
                                 "vsub.xyz vf5, vf5, vf6
"
                                 "sqc2 vf5, 0x0(%2)
"
                                 :
                                 : "r"(a + 0x20), "r"(p), "r"(&L.t0)
                                 : "memory");
            len = vlen(&L.t0);
            ratio = AI_GetInterRatioOutCut(len, 0.0f, *(float *)(p + 0x14), 1.0f, 0.0f);
            k = *(float *)(p + 0x10) * ratio / len;
            SCALE(&L.t0, &L.t1, k);
            L.t1.y = 0.0f;
            ADD3(*(char **)a + 0x140, &L.t1, *(char **)a + 0x140);
            p += 0x20;
            n--;
        } while (n != 0);
        o = *(char **)a;
    }
    s2 = a + 0x20;
    k = -*(float *)(o + 0x108);
    SCALE(a + 0x50, &L.t2, k);
    ADD3(*(char **)a + 0x140, &L.t2, *(char **)a + 0x140);
    o = *(char **)a;
    lim = *(float *)(o + 0x110) * 0.1f;
    vdist(a + 0x40, s2);
    s0 = (char *)&L.t3;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                         "lqc2 vf6, 0x0(%1)
"
                         "vsub.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%2)
"
                         :
                         : "r"(a + 0x40), "r"(s2), "r"(s0)
                         : "memory");
    len = vlen(s0);
    if (0.0f < len) {
        k = 1.0f / len;
        SCALE(s0, s0, k);
        o = *(char **)a;
    }
    ratio = AI_GetInterRatioOutCut4(len, 0.0f, *(float *)(o + 0xF0), 0.0f);
    ratio = ratio * ratio;
    SCALE(s0, &L.t4, ratio);
    rnd = iosGetRandom();
    if (rnd < lim)
        ADD3(*(char **)a + 0x140, &L.t4, *(char **)a + 0x140);
    func_00052790(a);
    o = *(char **)a;
    {
        float f4 = *(float *)(a + 0xC);
        char *q = *(char **)(o + 0x114);

        if (*(float *)(q + 0x38) < *(float *)(a + 8) * (f4 * *(float *)(q + 0x3C) + 1.0f) && *(float *)((char *)&gcGlobalVar + 0x68) < f4)
            func_00052558(a);
    }
    *(float *)(a + 0x74) = *(float *)(a + 0x74) + gcGlobalVar.f190;
}
#endif
