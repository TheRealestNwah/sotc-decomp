typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

typedef struct {
    char pad0[0x40];
    VecQ pos;
} ClipResult;

extern int func_000FAEC8(void *);
extern int pathJudgeFunc();
extern int ClipCollisionDirectCallBackDoubleSide(ClipResult *, float *, float *, void *, int, int, int, int, int (*)(), int);

static inline void vecSub(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

int pathDetectCollision(void *path, Vec4 *out, float *from, float *to, void *obj)
{
    ClipResult res;
    Vec4 d;

    if (obj == 0) {
        return 0;
    }
    if (ClipCollisionDirectCallBackDoubleSide(&res, to, from, obj, 2, func_000FAEC8(path), 0, 0, pathJudgeFunc, 0) == 0) {
        return 0;
    }
    vecSub(d, from, res.pos.f);
    vecNormalize(d);
    vecScale(d, d, 0.1f);
    vecAdd(res.pos.f, res.pos.f, d);
    res.pos.f[3] = 1.0f;
    *(u_long128 *)out = res.pos.q;
    return 1;
}
