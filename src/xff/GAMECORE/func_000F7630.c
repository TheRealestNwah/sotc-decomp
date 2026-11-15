/* Parked: 168 diffs, same size (174 words incl. the split tail at func_000F78D0). Three-point sweep test on an object with up to three anchor points (count at +0x380, points at +0x100 / +0x120 / +0x140 and a fallback at +0xA8/+0xB0, owner at +0x3C4, threshold at +0x3C8 with -1.0 meaning off): two ClipCollisionDirectCallBackOneObj probes (to the first/second point and between them) must miss, then three unit direction vectors from the object are compared by VU0 dot products (dot3 block with an early-clobber output) against the +0x20 heading and the threshold, returning 1 when the sweep is accepted. Remaining: the Original merges the two movn point selections differently (s1/s2 roles and the pre-load order of the count and anchor addresses), which shifts the whole body; not diffed past the prologue. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern int ClipCollisionDirectCallBackOneObj(void *, void *, void *, int, int, int, int, int);

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

#define VSUB(a, b, d)                                           \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"                  \
                         "lqc2 vf6, 0x0(%1)\n"                  \
                         "vsub.xyzw vf7, vf5, vf6\n"            \
                         "sqc2 vf7, 0x0(%2)\n"                  \
                         :                                      \
                         : "r"(a), "r"(b), "r"(d)               \
                         : "memory")

static inline float dot3(void *a, void *b)
{
    int bits;
    float f;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         : "=&r"(bits)
                         : "r"(a), "r"(b)
                         : "memory");
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(bits));
    return f;
}

static int func_000F7630(char *o)
{
    struct {
        char hit1[0x50];
        char hit2[0x50];
        Vec d1;
        Vec d2;
        Vec d3;
        Vec d4;
    } L __attribute__((aligned(16)));
    char *s1 = 0;
    char *s2 = 0;
    unsigned int n;
    int r;
    float a;
    float b;
    char *src;
    Vec *c;
    Vec *d;

    n = *(unsigned int *)(o + 0x380);
    if (n != 0)
        s2 = o + 0x100;
    if (1 < n)
        s1 = o + 0x120;
    if (*(int *)(o + 0x3C4) != 0)
        r = ClipCollisionDirectCallBackOneObj(L.hit1, o, s1, *(int *)(o + 0x3C4), 0, 0, 0, 0);
    else
        r = 0;
    if (r != 0)
        return 0;
    if (*(int *)(o + 0x3C4) != 0)
        r = ClipCollisionDirectCallBackOneObj(L.hit2, s2, s1, *(int *)(o + 0x3C4), 0, 0, 0, 0);
    else
        r = 0;
    if (r != 0)
        return 0;
    if (*(float *)(o + 0x3C8) == -1.0f)
        return 1;
    VSUB(s2, o, &L.d1);
    VSUB(s1, o, &L.d2);
    NORM(&L.d1);
    NORM(&L.d2);
    a = dot3(o + 0x20, &L.d1);
    b = dot3(o + 0x20, &L.d2);
    if (!(a <= b)) {
        if (!(*(float *)(o + 0x3C8) <= b))
            return 0;
    }
    n = *(unsigned int *)(o + 0x380);
    if (n < 3) {
        if (*(int *)(o + 0xA8) == 0)
            return 1;
        L.d3.q = *(s128 *)(o + 0xB0);
    } else {
        src = (2 < n) ? o + 0x140 : 0;
        VSUB(src, s1, &L.d3);
        NORM(&L.d3);
    }
    VSUB(s1, s2, &L.d4);
    NORM(&L.d4);
    a = dot3(&L.d2, &L.d3);
    b = dot3(&L.d4, &L.d3);
    if (b <= a)
        return 1;
    if (*(float *)(o + 0x3C8) <= a)
        return 1;
    return 0;
}
#endif
