/* Parked: 103 diffs, same size (170 words). Path-follow state init (sibling of func_000479F0): scales the heading by the speed ratio, draws two random unit vectors (a with y cleared, b scaled by 0.2), derives the follow vector from o+0xE0 + b - o+0xB0, blends it 0.8/0.2 with a, rescales by 2/|v|, then refreshes A0/A4 and calls AI_GetAccelC/A/B3XYZ. All VU0 runs are inline asm that matches word for word. Remaining: register numbering only (the Original puts o/p in s1/s2 and the random-vector pointer in s0, ours allocates o/p to s0/s1; pins on the parameter copies add a $fp move). */
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
extern void iosGetDRandomVector(void *);
extern void AI_GetAccelA3XYZ(char *, char *, char *, char *, char *, char *, float);
extern void AI_GetAccelB3XYZ(char *, char *, char *, char *, char *, char *, float);
extern void AI_GetAccelC3XYZ(char *, char *, char *, char *, char *, char *, float);

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

void func_00045F40(char *o, char *p)
{
    Vec a __attribute__((aligned(16)));
    Vec b;
    char *s7;
    char *s0;
    char *s3;
    char *s4;
    char *s5;
    char *s6;
    float two;
    float f;
    float lim;
    int qb;

    two = 2.0f;
    s7 = p + 0x30;
    f = *(float *)(o + 0x354) / *(float *)(o + 0x350);
    SCALE(p + 0x90, s7, f);
    *(s128 *)(p + 0x50) = *(s128 *)(p + 0x80);
    iosGetDRandomVector(&a);
    s0 = (char *)&b;
    iosGetDRandomVector(&b);
    a.y = 0.0f;
    NORM(&a);
    NORM(&b);
    f = 0.19999999f;
    SCALE(&b, &b, f);
    s3 = p + 0x60;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         :
                         : "r"(o + 0xE0), "r"(&b), "r"(s3)
                         : "memory");
    s0 = p + 0x40;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         :
                         : "r"(s3), "r"(o + 0xB0), "r"(s0)
                         : "memory");
    *(float *)(p + 0x44) = 0.0f;
    NORM(s0);
    {
        int sb;
        float k = 0.79999995f;

        __asm__("mfc1 %0, %1" : "=r"(sb) : "f"(k));
        __asm__ __volatile__("qmtc2.ni %2, vf7\n"
                             "lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsubx.w vf8, vf0, vf7x\n"
                             "vmulax.xyzw ACC, vf5, vf7x\n"
                             "vmaddw.xyzw vf9, vf6, vf8w\n"
                             "sqc2 vf9, 0x0(%0)\n"
                             :
                             : "r"(s0), "r"(&a), "r"(sb)
                             : "memory");
    }
    *(float *)(p + 0x44) = 0.1f;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         : "=r"(qb)
                         : "r"(s0)
                         : "memory");
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(qb));
    f = two / f;
    SCALE(s0, s0, f);
    s4 = p + 0x70;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(s4) : "memory");
    *(float *)(p + 0xA0) = *(float *)(o + 0x44);
    s6 = p + 0x20;
    s5 = p + 0x50;
    *(float *)(p + 0xA4) = gcGlobalVar.f190 * *(float *)(o + 0x350);
    lim = gcGlobalVar.f190 * *(float *)(o + 0x350);
    if (*(float *)(o + 0x44) < lim)
        *(float *)(p + 0xA0) = lim;
    AI_GetAccelC3XYZ(s6, s7, s0, s5, s3, s4, *(float *)(p + 0xA0));
    AI_GetAccelA3XYZ(p, s7, s5, s3, s4, s6, *(float *)(p + 0xA0));
    AI_GetAccelB3XYZ(p + 0x10, s7, s0, s5, s3, s6, *(float *)(p + 0xA0));
}
#endif
