typedef int s128 __attribute__((mode(TI)));

extern char *B_00189DF4;
extern char *GetLayoutClass(void *);
extern void *isysGetThisSubThread(void);

static inline float distSq(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline float square(float x)
{
    return x * x;
}

int chkNearStickArrow(s128 *out, float *pos, float range)
{
    char *p;
    float r2;

    isysGetThisSubThread();
    r2 = range * range;
    p = B_00189DF4;
    while (p != 0) {
        char *next;
        char *c = GetLayoutClass(*(void **)(p + 0x94));

        next = *(char **)(p + 0xC0);
        if (*(short *)(p + 0xA0) == 1 || *(short *)(p + 0xA0) == 2 || *(short *)(p + 0xA0) == 4 || *(short *)(p + 0xA0) == 5 || *(short *)(p + 0xA0) == 6) {
            float *v = *(float **)(c + 0x134);
            if (distSq(v, pos) < r2 && *(float *)(p + 0x98) <= 0.5f) {
                *out = *(s128 *)v;
                return 1;
            }
        }
        p = next;
    }
    return 0;
}
