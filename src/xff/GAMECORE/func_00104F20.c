/* func_00104F20: sets up the fast-leg control work's attain range (target position and
 * direction, their angles in the root frame, and whether the target lies inside the
 * owner's judge volume). */
typedef float Vec4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));
typedef struct {
    int x[8];
} __attribute__((aligned(8))) Blk;
typedef union {
    u128 q;
    int i[4];
} Q4;

extern int *DldSysUndefSymbol;
extern int calcAttainPosForAttainRange(char *, int *, float *, float *, void *, int, int);
extern void calcAttainRangeData(void *, void *, int);
extern float iosGetATan2fExact(float, float);
extern int CheckPositionInsideOfJudgeVolumeObject(void *, void *, void *, void *);

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


static inline void vecUnit(void *d)
{
    __asm__ __volatile__("sqc2 $vf0, 0x0(%0)\n" : : "r"(d) : "memory");
}

static inline float vecLen(void *s)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(s) : "$2", "memory");
    return r;
}

static inline float xzDist(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}

static inline char *dldElem(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((*h >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

typedef union {
    int i;
    float f;
} IF;

static void func_00104F20(char *w)
{
    Vec4 d0, d1, d2, d3, p, q;
    char buf[0x60];
    int idx;
    char *own;
    float a;

    *(int *)(w + 0x144) = 0;
    *(int *)(w + 0x148) = 0;
    *(int *)(w + 0x14C) = 0;
    own = *(char **)(w + 0xCC);
    vecUnit(w + 0x150);
    *(int *)(w + 0x1A0) = 0;
    *(Blk *)(w + 0x180) = *(Blk *)(*(char **)(w + 4) + 0x3E0);
    applyMatrix(d3, w + 0x20, *(char **)(w + 0x18) + 0x30);
    d3[1] = 0.0f;
    *(float *)(w + 0x140) = vecLen(d3);
    if (*(void **)(w + 0xC) == 0)
        return;
    if (*(void **)(w + 0x10) != 0) {
        (*(Q4 *)(w + 0x120)).q = (**(Q4 **)(w + 0xC)).q;
        vecSub(d0, w + 0x120, *(char **)(w + 4) + 0x30);
        vecSub(d1, *(void **)(w + 0x10), *(void **)(w + 0xC));
    } else {
        if (calcAttainPosForAttainRange(w, &idx, p, q, *(void **)(w + 0xC), 0, 0)) {
            *(int *)(w + 0x14C) = 1;
            *(int *)(w + 0x1A0) = 1;
            *(Blk *)(w + 0x180) = *(Blk *)(*(char **)(w + 4) + 0x3E0);
            (*(Q4 *)(w + 0x150)).q = (*(Q4 *)q).q;
            (*(Q4 *)(w + 0x120)).q = (*(Q4 *)p).q;
            calcAttainRangeData(w + 0x180, *(char **)(w + 4) + 0x3E0, idx);
        } else {
            (*(Q4 *)(w + 0x120)).q = (**(Q4 **)(w + 0xC)).q;
            (*(Q4 *)(w + 0x150)).q = (*(Q4 *)(*(char **)(w + 4) + 0xB0)).q;
            *(int *)(w + 0x14C) = *(int *)(*(char **)(w + 4) + 0xA8);
        }
        vecSub(d0, w + 0x120, *(void **)(*(char **)(w + 0x18) + 0x134));
        (*(Q4 *)d1).q = (*(Q4 *)d0).q;
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
    applyMatrix(w + 0x100, w + 0x20, w + 0x120);
    applyMatrix(w + 0x110, w + 0x20, *(void **)(*(char **)(w + 0x18) + 0x134));
    *(float *)(w + 0xE4) = 0.0f;
    *(float *)(w + 0xD4) = 0.0f;
    *(float *)(w + 0xF4) = 0.0f;
    vecNormalize(w + 0xE0, w + 0xE0);
    vecNormalize(w + 0xD0, w + 0xD0);
    vecNormalize(w + 0xF0, w + 0xF0);
    a = iosGetATan2fExact(*(float *)(w + 0xE0), *(float *)(w + 0xE8));
    *(float *)(w + 0x130) = iosGetATan2fExact(*(float *)(w + 0xD0), *(float *)(w + 0xD8));
    *(float *)(w + 0x134) = iosGetATan2fExact(*(float *)(w + 0xF0), *(float *)(w + 0xF8));
    *(float *)(w + 0x138) = a - *(float *)(w + 0x130);
    *(float *)(w + 0x13C) = xzDist(w + 0x110, w + 0x100);
    applyMatrix(w + 0x160, w + 0x20, w + 0x150);
    *(float *)(w + 0x164) = 0.0f;
    vecNormalize(w + 0x160, w + 0x160);
    ((IF *)(w + 0x170))->f = iosGetATan2fExact(*(float *)(w + 0x160), *(float *)(w + 0x168));
    if (*(int *)(own + 0x38) != 0
        || (*(void **)(own + 0x24) != 0 && dldElem(*(unsigned int **)(own + 0x24)) != 0
            && CheckPositionInsideOfJudgeVolumeObject(buf, *(void **)(w + 8), *(void **)(own + 0x24), w + 0x120))) {
        *(int *)(w + 0x148) = 1;
    }
}
