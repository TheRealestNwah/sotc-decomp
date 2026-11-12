typedef int s128 __attribute__((mode(TI)));

extern int func_00049DA0(char *, float *, int);

static inline void sub4(float *d, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void add4(float *d, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void add3(float *d, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(b) : "memory");
}

static inline void normalize3(float *v)
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

static inline void scale4(float *v, float s)
{
    int si;
    __asm__ __volatile__("mfc1 %0, %1" : "=r"(si) : "f"(s));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(si) : "memory");
}

#ifdef NONMATCHING /* 18 diffs: vector-pointer register numbering and early addiu scheduling */
static void func_00049FF8(char *p)
{
    float t[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    float s;
    float u[4] __attribute__((aligned(16)));
    int idx = func_00049DA0(p, u, *(int *)(p + 0x98));
    char *base;
    int i;

    *(int *)(p + 0x98) = idx;
    if (idx < *(int *)(p + 0x84) && idx > 0 && *(int *)(p + 0x8C)) {
        base = *(char **)(p + 0x70);
        sub4(d, (float *)(base + idx * 16 - 16), (float *)(base + idx * 16));
        normalize3(d);
        scale4(d, u[0]);
        add4(q, (float *)(base + *(int *)(p + 0x98) * 16), d);
        sub4(t, (float *)(p + 0xB0), q);
        add3((float *)(p + 0x150), t);
        add3((float *)(p + 0x180), t);
        add3((float *)(p + 0x320), t);
        {
            float *c = (float *)base;
            for (i = 0; i < *(int *)(p + 0x84); i++, c += 4)
                add4(c, c, t);
        }
    }
}
#endif
