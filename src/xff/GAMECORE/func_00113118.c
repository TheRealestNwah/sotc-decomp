extern float YUnitVector[4];
extern char gcGlobalVar[];
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, void *, int, int, void *, int);

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
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static void func_00113118(char *p, float *q)
{
    float res[20] __attribute__((aligned(16)));
    union { float f[4]; long long l[2]; } end __attribute__((aligned(16)));
    union { float f[4]; long long l[2]; } start __attribute__((aligned(16)));
    char *c = *(char **)(p + 0xCC);

    vecScale(start.f, YUnitVector, -*(float *)(c + 0xC4));
    vecScale(end.f, YUnitVector, *(float *)(c + 0xC4));
    vecAdd(start.f, start.f, q);
    vecAdd(end.f, end.f, q);
    start.f[3] = 1.0f;
    end.f[3] = 1.0f;
    if (ClipCollisionDirectCallBack(res, end.f, start.f, gcGlobalVar + 0x238, 0, 0, 0,
                                    *(void **)(c + 0xF0), 0)) {
        q[1] = res[17] + *(float *)(c + 0xC0);
    }
}
