/* Parked: 19 diffs, same size (170 words incl. the split tail func_000FFE10). Direction-set builder for a two-target follower: with the target pointer at +0xC (clears owner+0xCC +0x154 and returns when null) it forms t = target - position and u = second target - target (or t when there is no second target, in which case y at +0x134 drifts by owner+0xCC +0xF4 unless the object at +4 has +0xE0 set), sets w = 1, normalises t, u and t + u, rotates them (and the stored target and the layout position) by the matrix at +0x20 into +0xF0, +0xE0, +0x100, +0x110, +0x120, renormalises the first three and calls getTurnAndPitchFromDir on +0xE0 for +0x140/+0x144. VU0 runs match word for word. Remaining: address-register numbering only (the Original keeps &u in t0 and the matApply destinations in a3/a0/a2; pointer locals for them made it worse, 37). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern void getTurnAndPitchFromDir(void *, void *, void *);

#define NORM(v)                                                     __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"                                           "vmul.xyz vf7, vf5, vf5
"                                      "vmulax.w ACC, vf0, vf7x
"                                     "vmadday.w ACC, vf0, vf7y
"                                    "vmaddz.w vf7, vf0, vf7z
"                                     "vrsqrt Q, vf0w, vf7w
"                                        "vwaitq
"                                                      "vmulq.xyz vf5, vf5, Q
"                                       "sqc2 vf5, 0x0(%0)
"                                           :                                                               : "r"(v)                                                        : "memory")

#define VSUB(a, b, d)                                               __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"                                           "lqc2 vf6, 0x0(%1)
"                                           "vsub.xyzw vf7, vf5, vf6
"                                     "sqc2 vf7, 0x0(%2)
"                                           :                                                               : "r"(a), "r"(b), "r"(d)                                        : "memory")

static inline void matApply(float *out, float *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%2)\n"
                         : : "r"(v), "r"(m), "r"(out) : "memory");
}

static void func_000FFB80(char *o)
{
    struct {
        Vec t;
        Vec u;
        Vec v;
    } L __attribute__((aligned(16)));
    char *a;
    char *b;
    char *lay;
    char *m;

    a = *(char **)(o + 0xC);
    if (a == 0) {
        *(int *)(*(char **)(o + 0xCC) + 0x154) = 0;
        return;
    }
    b = *(char **)(o + 0x10);
    if (b != 0) {
        VSUB(a, *(char **)(o + 4) + 0x30, &L.t);
        VSUB(*(char **)(o + 0x10), *(char **)(o + 0xC), &L.u);
        *(s128 *)(o + 0x130) = **(s128 **)(o + 0xC);
    } else {
        lay = *(char **)(o + 0x18);
        VSUB(a, *(char **)(lay + 0x134), &L.t);
        L.u.q = L.t.q;
        *(s128 *)(o + 0x130) = **(s128 **)(o + 0xC);
        if (*(int *)(*(char **)(o + 4) + 0xE0) == 0)
            *(float *)(o + 0x134) = *(float *)(o + 0x134) + *(float *)(*(char **)(o + 0xCC) + 0xF4);
    }
    L.t.w = 1.0f;
    L.u.w = 1.0f;
    NORM(&L.t);
    NORM(&L.u);
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)
lqc2 vf6, 0x0(%1)
vadd.xyzw vf7, vf5, vf6
sqc2 vf7, 0x0(%2)
"
                         : : "r"(&L.t), "r"(&L.u), "r"(&L.v) : "memory");
    L.v.w = 1.0f;
    NORM(&L.v);
    m = o + 0x20;
    matApply((float *)(o + 0xF0), (float *)m, (float *)&L.v);
    matApply((float *)(o + 0xE0), (float *)m, (float *)&L.t);
    matApply((float *)(o + 0x100), (float *)m, (float *)&L.u);
    matApply((float *)(o + 0x110), (float *)m, (float *)(o + 0x130));
    matApply((float *)(o + 0x120), (float *)m, *(float **)(*(char **)(o + 0x18) + 0x134));
    NORM(o + 0xF0);
    NORM(o + 0xE0);
    NORM(o + 0x100);
    getTurnAndPitchFromDir(o + 0xE0, o + 0x140, o + 0x144);
}
#endif
