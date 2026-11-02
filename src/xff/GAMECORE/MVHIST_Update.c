typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 a[90];
    s128 b[90];
    s128 sum;
    /* A union, so the weight store doesn't let gcc reuse the loaded count. */
    union {
        float f;
        int i;
    } w[90];
    int count;
} MvHist;

extern char gcGlobalVar[];
extern char *GetLayoutClass(void *);

static inline void vecScaleXYZ(void *dst, void *src, float s)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "mfc1 $8, %2\n"
                         "qmtc2.ni $8, vf5\n"
                         "vmulx.xyz vf6, vf4, vf5x\n"
                         "vmove.w vf6, vf0\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "f"(s) : "$8", "memory");
}

static inline void vecScaleXYZW(void *dst, void *src, float s)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "mfc1 $8, %2\n"
                         "qmtc2.ni $8, vf5\n"
                         "vmulx.xyzw vf6, vf4, vf5x\n"
                         "vmove.w vf6, vf0\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "f"(s) : "$8", "memory");
}

static inline void zero(void *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

static inline void copy(void *dst, void *src)
{
    __asm__ __volatile__("lq $8, 0x0(%1)\n"
                         "sq $8, 0x0(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "memory");
}

static inline void vecAdd(void *dst, void *b)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%0)\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "vadd.xyzw vf6, vf4, vf5\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(dst), "r"(b) : "memory");
}

void MVHIST_Update(MvHist *h, void *obj)
{
    char *layout = GetLayoutClass(obj);
    float total = 0.0f;
    s128 *sum = &h->sum;
    int i;
    int n;

    zero(sum);
    h->w[h->count].f = *(float *)(gcGlobalVar + 0x180);
    n = h->count;
    vecScaleXYZ(&h->a[n], layout + 0x30, h->w[n].f);
    copy(&h->b[n], *(void **)(layout + 0x134));
    __asm__ __volatile__("vsub.xyzw vf6, vf0, vf0\n");
    for (i = 0; i < 90; i++) {
        vecAdd(&h->sum, &h->a[i]);
        total += h->w[i].f;
    }
    vecScaleXYZW(sum, sum, 1.0f / total);
    h->count = n + 1;
    if (n + 1 >= 90)
        h->count = 0;
}
