typedef float Vec145[4] __attribute__((aligned(16)));

typedef struct Work145 {
    char pad0[0x180];
    Vec145 a[0x30];
    Vec145 b[0x18];
    Vec145 c[0x18];
    int count;
} Work145;

static inline void CopyVector145(float *dst, float *src)
{
    __asm__ __volatile__("lq $8, 0x0(%1)\n"
                         "sq $8, 0x0(%0)\n"
                         :
                         : "r"(dst), "r"(src)
                         : "$8", "memory");
}

static void func_000145C8(Work145 *dst, Work145 *src, int i)
{
    int n = dst->count;

    CopyVector145(dst->a[n], src->a[i]);
    CopyVector145(dst->b[n], src->b[i]);
    CopyVector145(dst->c[n], src->c[i]);
    dst->count = n + 1;
}
