typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float distanceSquareXZ(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

void AI_UpdateChildPathWork(char *work)
{
    void *obj = *(void **)(work + 0xF0);
    char *layout;
    float *point;
    float radius, height, r2, half;
    Vec4 pos;

    isysGetThisSubThread();
    layout = GetLayoutClass(obj);
    radius = *(float *)(work + 0xE0);
    height = *(float *)(work + 0xE4);
    r2 = radius * radius;
    pos.q = *(s128 *)(work + 0x10);
    vecAdd(pos.f, pos.f, (float *)(work + 0xD0));
    *(int *)(work + 0xE8) = 0;
    *(int *)(work + 0xEC) = 0;
    half = height * 0.5f;
    point = (float *)*(int *)(layout + 0x134);
    if (point[1] < pos.f[1] - half)
        return;
    if (pos.f[1] + half < point[1])
        return;
    if (r2 < distanceSquareXZ(point, pos.f))
        return;
    *(int *)(work + 0xE8) = 1;
    *(int *)(work + 0xEC) = 1;
}
