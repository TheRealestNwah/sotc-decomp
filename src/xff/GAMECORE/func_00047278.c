/* Parked: 104 diffs, same size (187 words incl. the split tail func_00047538). Path-follow init (sibling of func_00045F40 / func_00052790): rotates the constant offset RO_0017D1A0 (-0.02, 0.1, 0, 0) and ZUnitVectorInv by the layout's quaternion (VU0 quaternion-to-matrix applied from registers), adds the rotated offset to the layout position, forces the rotated Z vector's y to 1.0 and normalises it, derives the move vector from w+0x60 - w+0x50 scaled by 1/length and by o+0x358, copies w+0x90 to w+0x30, raises w+0xA0 to f190 * o+0x350 and calls AI_GetAccelC/A/B3XYZ. The frame addresses (&z, &p) are held in locals assigned first so they take s0/s1 as in the Original, and w+0x70 is hoisted before the first call so it takes s7. Remaining: the Original copies RO_0017D1A0 into the frame with a different ld order and keeps o/w in s2/s3 with the two locals reused for w+0x50 / w+0x40 after their last use (using one variable for both made it worse). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

typedef struct {
    long lo;
    long hi;
} Pair;

extern struct {
    char pad[0x190];
    float f190;
} gcGlobalVar;
extern Pair RO_0017D1A0;
extern Vec ZUnitVectorInv;
extern char *GetLayoutClass(int);
extern void AI_GetAccelA3XYZ(char *, char *, char *, char *, char *, char *, float);
extern void AI_GetAccelB3XYZ(char *, char *, char *, char *, char *, char *, float);
extern void AI_GetAccelC3XYZ(char *, char *, char *, char *, char *, char *, float);

#define QMATRIX                                                 \
    "vaddw.xyz vf12, vf0, vf0w\n"                               \
    "lqc2 vf11, 0x0(%1)\n"                                      \
    "vmr32.w vf14, vf0\n"                                       \
    "vmr32.w vf15, vf0\n"                                       \
    "vmr32.w vf16, vf0\n"                                       \
    "vopmula.xyz ACC, vf11, vf12\n"                             \
    "vmadd.xyz vf11, vf0, vf0\n"                                \
    "vmadd.xyz vf10, vf11, vf12\n"                              \
    "vmul.xyz vf13, vf11, vf10\n"                               \
    "vopmula.xyz ACC, vf11, vf10\n"                             \
    "vmaddw.xyz vf15, vf10, vf11w\n"                            \
    "vmsubw.xyz vf16, vf10, vf11w\n"                            \
    "vopmula.xyz ACC, vf13, vf12\n"                             \
    "vmadd.xyz vf17, vf13, vf12\n"                              \
    "vopmula.xyz ACC, vf15, vf12\n"                             \
    "vmadd.xyz vf15, vf0, vf0\n"                                \
    "vsub.xyz vf14, vf12, vf17\n"                               \
    "vmove.yz vf17, vf14\n"                                     \
    "vmove.y vf14, vf16\n"                                      \
    "vmove.y vf16, vf15\n"                                      \
    "vmove.y vf15, vf17\n"                                      \
    "vmove.z vf14, vf15\n"                                      \
    "vmove.z vf15, vf16\n"                                      \
    "vmove.z vf16, vf17\n"

#define ROTATE(v, quat)                                         \
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n" QMATRIX          \
                         "vmulax.xyzw ACC, vf14, vf8x\n"        \
                         "vmadday.xyzw ACC, vf15, vf8y\n"       \
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"       \
                         "vmaddw.xyzw vf10, vf0, vf8w\n"        \
                         "sqc2 vf10, 0x0(%0)\n"                 \
                         :                                      \
                         : "r"(v), "r"(quat)                    \
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

static void func_00047278(char *o, char *w)
{
    struct {
        Vec t;
        Vec p;
        Vec z;
        Pair off;
    } L __attribute__((aligned(16)));
    char *lay;
    char *s0;
    char *s1;
    char *s4;
    char *s5;
    char *s6;
    char *s7;
    float len;
    float inv;
    float f12;
    float k;
    int bits;
    char *pz;
    char *pp;

    pz = (char *)&L.z;
    pp = (char *)&L.p;
    s7 = w + 0x70;
    lay = GetLayoutClass(*(int *)(o + 8));
    L.off.lo = RO_0017D1A0.lo;
    L.off.hi = RO_0017D1A0.hi;
    L.p.q = **(s128 **)(lay + 0x134);
    ROTATE(&L.off, *(char **)(lay + 0x13C));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%0)\n"
                         : : "r"(pp), "r"(&L.off) : "memory");
    L.z.q = ZUnitVectorInv.q;
    ROTATE(pz, *(char **)(lay + 0x13C));
    L.z.y = 1.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(pz) : "memory");
    *(s128 *)(w + 0x60) = L.p.q;
    s5 = w + 0x60;
    s0 = w + 0x50;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvsub.xyzw vf7, vf5, vf6\nsqc2 vf7, 0x0(%2)\n"
                         : : "r"(s5), "r"(s0), "r"(&L.t) : "memory");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         : "=&r"(bits) : "r"(&L.t) : "memory");
    __asm__("mtc1 %1, %0" : "=f"(len) : "r"(bits));
    inv = 1.0f / len;
    SCALE(&L.t, &L.t, inv);
    s1 = w + 0x40;
    k = *(float *)(o + 0x358);
    SCALE(&L.t, s1, k);
    f12 = *(float *)(w + 0xA0);
    s6 = w + 0x20;
    *(s128 *)(w + 0x30) = *(s128 *)(w + 0x90);
    s4 = w + 0x30;
    k = gcGlobalVar.f190 * *(float *)(o + 0x350);
    if (f12 < k) {
        *(float *)(w + 0xA0) = k;
        f12 = k;
    }
    AI_GetAccelC3XYZ(s6, s4, s1, s0, s5, s7, f12);
    AI_GetAccelA3XYZ(w, s4, s0, s5, s7, s6, *(float *)(w + 0xA0));
    AI_GetAccelB3XYZ(w + 0x10, s4, s1, s0, s5, s6, *(float *)(w + 0xA0));
}
#endif
