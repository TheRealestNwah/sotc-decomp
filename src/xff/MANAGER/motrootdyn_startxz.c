typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroVector;
extern void GetGeometryPointerPosition(float *, void *);
extern int ParentLayoutObj(void *, void *);
extern void ForceUnparentLayoutObj(void *);

static inline void subVector(float *out, void *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void motrootdyn_startxz(void *obj, char *ch)
{
    char *gp = ch + 0xF70;

    if (*(int *)(ch + 0xFBC) != 0) {
        float pos[4] __attribute__((aligned(16)));
        float *v;

        GetGeometryPointerPosition(pos, gp);
        v = (float *)(ch + 0x6D0);
        subVector(v, *(void **)(ch + 0x134), pos);
        *(int *)(ch + 0x6D0) = 0;
        *(int *)(ch + 0x6D8) = 0;
        ParentLayoutObj(obj, gp);
    } else if (*(int *)(ch + 0x124) != 0) {
        *(int *)(ch + 0x6D0) = 0;
        *(int *)(ch + 0x6D8) = 0;
    } else if (*(int *)(ch + 0xF3C) != 0) {
        ParentLayoutObj(obj, ch + 0xEF0);
    } else {
        ForceUnparentLayoutObj(obj);
    }
    *(s128 *)(ch + 0xAB0) = ZeroVector;
}
