extern char *GetLayoutClass(void *);

static inline int AI_CheckPathPoint(void *obj, float *pos, float r, float h)
{
    float r2 = r * r;
    char *c = GetLayoutClass(obj);
    float *p;
    float half;
    float d;

    if (c == 0)
        return 0;
    half = h * 0.5f;
    p = *(float **)(c + 0x134);
    if (p[1] < pos[1] - half)
        return 0;
    if (pos[1] + half < p[1])
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(p), "r"(pos) : "$2");
    if (r2 < d)
        return 0;
    return 1;
}

extern void updateUserPathWork(void *, void *);

static inline void vecAddXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void AI_UpdateLeaderPathWork(void *path, char *w)
{
    char *pw = w + 0x120;
    float pos[4] __attribute__((aligned(16)));

    if (path != 0 && *(int *)(w + 4) >= 0) {
        updateUserPathWork(*(void **)(w + 0xF0), path);
        return;
    }
    vecAddXYZ(pos, (float *)pw, (float *)(w + 0x1A0));
    *(int *)(pw + 0x98) = AI_CheckPathPoint(*(void **)(pw + 0xC8), pos, *(float *)(pw + 0x90), *(float *)(pw + 0x94));
}
