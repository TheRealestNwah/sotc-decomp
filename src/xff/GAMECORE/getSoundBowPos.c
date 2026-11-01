typedef int s128 __attribute__((mode(TI)));

extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern char *B_00189DF4;
extern const union {
    int i;
    float f;
} RO_0017CFA4;

int getSoundBowPos(s128 *out, float *pos)
{
    float best;
    char *e;
    char *next;

    isysGetThisSubThread();
    best = RO_0017CFA4.f;
    for (e = B_00189DF4; e != 0; e = next) {
        char *c = GetLayoutClass(*(void **)(e + 0x94));

        next = *(char **)(e + 0xC0);
        if (*(int *)(e + 0x48) == 6 && *(short *)(e + 0xA0) == 0) {
            float d;

            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "vmul.xyz vf7, vf7, vf7\n"
                                 "vaddy.x vf7, vf7, vf7y\n"
                                 "vaddz.x vf7, vf7, vf7z\n"
                                 "qmfc2.ni $2, vf7\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(d) : "r"(*(float **)(c + 0x134)), "r"(pos) : "$2");
            if (d < best) {
                best = d;
                *out = **(s128 **)(c + 0x134);
            }
        }
    }
    if (best == RO_0017CFA4.f)
        return 0;
    return 1;
}
