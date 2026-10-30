typedef float Vec4[4] __attribute__((aligned(16)));

extern float *getGoalPointDataByAreaIdx(void *, int, int);
extern void setAttainmentPosAndDir(void *, float *, float *);
extern void setUserPathMode(void *, int);

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

#define W(type, o) (*(type *)(work + (o)))

static void func_000FC0D0(char *work, char *layout)
{
    Vec4 pos;
    Vec4 dir;
    float *goal = getGoalPointDataByAreaIdx(work, W(int, 0x3C90), W(int, 0x3C8C));

    if (goal == 0)
        return;
    vecSub(dir, *(float **)(layout + 0x134), goal);
    dir[1] = 0;
    vecNormalize(dir);
    vecScale(pos, dir, W(float, 0x3C84));
    vecAdd(pos, pos, goal);
    pos[3] = 1.0f;
    dir[3] = 1.0f;
    setAttainmentPosAndDir(work, pos, dir);
    setUserPathMode(work, 0);
}
