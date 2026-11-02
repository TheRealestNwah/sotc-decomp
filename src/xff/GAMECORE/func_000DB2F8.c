extern void func_000DB328(void *, void *, void *, float *);

static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000DB2F8(void *a, void *b, void *c, float *from, float *to)
{
    float d[4] __attribute__((aligned(16)));

    vecSub(d, to, from);
    func_000DB328(a, b, c, d);
}
