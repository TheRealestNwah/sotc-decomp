typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef union {
    char *p;
    float f;
} Word;

extern float func_000DA5A8(Vec4 *);
extern float func_000DA5D8(Vec4 *, void *);

static inline void vecNormalize(float *dst, float *src)
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
                         : : "r"(dst), "r"(src) : "memory");
}

static inline int curStatus(char *sm)
{
    return *(int *)(sm + 8);
}

static void func_000DA4D0(char *a, Word *b, void *c)
{
    char *sm = a + 0x40;

    *(float *)(a + 0x20) = 0.0f;
    *(float *)(a + 0x28) = 0.0f;
    if (*(int *)(b->p + 0xE8) == 1 && curStatus(sm) == 1) {
        Vec4 *dir = (Vec4 *)(a + 0x60);
        float d = func_000DA5A8(dir);

        *(float *)(a + 0x20) = d;
        if (0.0f < d && d <= 1.39626348f) {
            Vec4 v;

            v.q = dir->q;
            v.f[1] = 0.0f;
            vecNormalize(v.f, v.f);
            *(float *)(a + 0x28) = func_000DA5D8(&v, c);
        }
    }
}
