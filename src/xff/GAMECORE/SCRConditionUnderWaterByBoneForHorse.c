extern int *DldSysUndefSymbol;
extern char gcGlobalVar[];
extern float YUnitVector[];
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern int CheckUnderVariableXZSurface(int, float *, float *, void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = 0;

    if (off != 0)
        t = *(int **)((char *)h - off);
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "qmtc2.ni %2, vf6
"
                         "vmulx.xyzw vf5, vf5, vf6x
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAddXYZ(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

int SCRConditionUnderWaterByBoneForHorse(void *actor, int a1, int a2, int a3, int a4, int a5, int a6, int a7, float up, float down,
       unsigned int *bone)
{
    float pos[4] __attribute__((aligned(16)));
    float hi[4] __attribute__((aligned(16)));
    float lo[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));

    GetMotionNodeQuaternionPos(q, pos, actor, *(int *)(dldResolve(bone) + 8), 1);
    vecScale(hi, YUnitVector, up);
    vecAddXYZ(hi, hi, pos);
    hi[3] = 1.0f;
    vecScale(lo, YUnitVector, down);
    vecAddXYZ(lo, lo, pos);
    lo[3] = 1.0f;
    return CheckUnderVariableXZSurface(0, hi, lo, gcGlobalVar + 0x234) != 0;
}
