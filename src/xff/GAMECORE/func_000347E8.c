typedef int s128 __attribute__((mode(TI)));

extern char *GetLayoutClass(void *);
extern void UpdateLayoutClassGeometry(void *);
extern s128 ZeroVector;
extern char gcGlobalVar[];

static inline void vecScale3(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecSub(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static void func_000347E8(char *obj)
{
    char *lc = GetLayoutClass(*(void **)(obj + 0x94));
    char *g;

    UpdateLayoutClassGeometry(lc);
    g = gcGlobalVar;
    if (*(float *)(g + 0x180) != 0.0f) {
        float *v = (float *)(lc + 0x30);
        vecSub(v, *(float **)(lc + 0x134), *(float **)(lc + 0x138));
        vecScale3(v, v, *(float *)(g + 0x184));
    } else {
        *(s128 *)(lc + 0x30) = ZeroVector;
    }
}
