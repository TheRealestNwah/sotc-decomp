#ifdef NONMATCHING
/* 6 diffs, same length. In the near-target branch the Original reloads the
   probe position from w+0xC before loading the target's position pointer
   (o+0x134) into $v1; ours schedules that pointer load first, into $a0. */
typedef float Vec4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));

extern char ZUnitVector[];
extern void func_001130A8(char *p, float *q);
extern void getTurnAndPitchFromDir(void *, void *, void *);

static inline void vecSub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline float distXZ(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2", "memory");
    return d;
}

static inline void vecNormalize(void *d, void *s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(s) : "memory");
}

static inline void applyMatrix(void *d, void *m, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

void func_001106D0(char *w)
{
    Vec4 d0, d1, d2, a, b;
    char *prm;
    char *o;

    *(int *)(w + 0x164) = 0;
    prm = *(char **)(w + 0xCC);
    if (*(void **)(w + 0xC) == 0)
        return;
    *(u128 *)a = **(u128 **)(w + 0xC);
    func_001130A8(w, a);
    if (*(void **)(w + 0x10) != 0) {
        *(u128 *)b = **(u128 **)(w + 0x10);
        func_001130A8(w, b);
        vecSub(d0, a, *(char **)(w + 4) + 0x30);
        vecSub(d1, b, a);
    } else {
        o = *(char **)(w + 0x18);
        if (distXZ(a, *(void **)(o + 0x134)) < *(float *)(prm + 0xB8)) {
            *(u128 *)a = **(u128 **)(w + 0xC);
            vecSub(d0, a, *(void **)(o + 0x134));
            *(int *)(w + 0x164) = 1;
        } else {
            *(int *)(w + 0x164) = 0;
            vecSub(d0, a, *(char **)(w + 4) + 0x30);
        }
        *(u128 *)d1 = *(u128 *)d0;
    }
    d0[3] = 1.0f;
    d1[3] = 1.0f;
    vecNormalize(d0, d0);
    vecNormalize(d1, d1);
    vecAdd(d2, d0, d1);
    d2[3] = 1.0f;
    vecNormalize(d2, d2);
    applyMatrix(w + 0xE0, w + 0x20, d2);
    applyMatrix(w + 0xD0, w + 0x20, d0);
    applyMatrix(w + 0xF0, w + 0x20, d1);
    applyMatrix(w + 0x100, w + 0x20, a);
    applyMatrix(w + 0x110, w + 0x20, *(void **)(*(char **)(w + 0x18) + 0x134));
    applyMatrix(w + 0x120, w + 0x20, *(char **)(w + 4) + 0x30);
    vecNormalize(w + 0xE0, w + 0xE0);
    vecNormalize(w + 0xD0, w + 0xD0);
    vecNormalize(w + 0xF0, w + 0xF0);
    getTurnAndPitchFromDir(w + 0xD0, w + 0x158, w + 0x15C);
    applyMatrix(w + 0x140, w + 0x60, ZUnitVector);
    getTurnAndPitchFromDir(w + 0x140, w + 0x150, w + 0x154);
    *(float *)(w + 0x160) = *(float *)(prm + 0x70);
}
#endif
