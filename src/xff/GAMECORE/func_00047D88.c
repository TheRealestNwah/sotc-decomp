/* Parked: 104 diffs, same size (158 words; Original continues into the split tail func_00047FD0, a tail call to func_000479F0). Animal path-follow step: updates velocity, compares the squared distances (VU0 sum of squares; vrsqrt .word, Q read by cfc2.ni) against a speed limit, advances the cursor at +0x340, and when it changes scans the path (+0x70) for the next point whose scaled distance fits, then picks a random duration and calls func_000479F0. Remaining: float register order of the two Q results (Original f3/f2, ours f1/f3), a1 vs a0 for the cursor, and delay-slot choices in the early returns. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern void AI_UpdateVelocity(char *, float, float);
extern float AI_GetRandomRange(float, float);
extern void func_00046F48(char *, char *);
extern void func_00047278(char *, char *, char *, char *);
extern void func_00047C78(char *);
extern void func_000479F0(char *, char *, float, float, float);

void func_00047D88(char *o)
{
    char *w;
    int old;
    int cur;
    int hit;
    float qa;
    float qb;
    float lim;
    float r;
    float pa;
    float pb;
    char *p180;
    char *p190;
    char *p160;

    w = o + 0x100;
    old = *(int *)(o + 0x340);
    AI_UpdateVelocity(o + 0x358, 25.0f, 10.0f);
    p180 = o + 0x180;
    p190 = o + 0x190;
    p160 = o + 0x160;
    pb = *(float *)(w + 0xA4);
    pa = *(float *)(w + 0xA0);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(qa)
                         : "r"(p180), "r"(p160)
                         : "$2", "memory");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(qb)
                         : "r"(p190)
                         : "$2", "memory");
    lim = *(float *)(gcGlobalVar + 0x190) * *(float *)(o + 0x350);
    hit = 1;
    if (!(qa <= qb * lim) && !(pa < pb))
        hit = 0;
    if (hit != 0)
        *(int *)(o + 0x340) = *(int *)(o + 0x340) + 1;
    cur = *(int *)(o + 0x340);
    if (!(cur < *(int *)(o + 0x84)))
        return;
    if (cur == old) {
        func_00046F48(o, w);
    } else {
        *(s128 *)(w + 0x30) = *(s128 *)(w + 0x90);
        if (!(*(int *)(o + 0x340) < *(int *)(o + 0x84)))
            return;
        do {
            *(s128 *)(w + 0x50) = *(s128 *)(*(char **)(o + 0x70) + (cur << 4));
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "vmul.xyz vf7, vf7, vf7\n"
                                 "vmulax.w ACC, vf0, vf7x\n"
                                 "vmadday.w ACC, vf0, vf7y\n"
                                 "vmaddz.w vf7, vf0, vf7z\n"
                                 ".word 0x4BA703BD\n"
                                 "vwaitq\n"
                                 "cfc2.ni $2, $vi22\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(qa)
                                 : "r"(w + 0x50), "r"(w + 0x60)
                                 : "$2", "memory");
            qa = qa / *(float *)(o + 0x358);
            *(float *)(w + 0xA0) = qa;
            lim = *(float *)(gcGlobalVar + 0x190) * *(float *)(o + 0x350);
            *(float *)(w + 0xA4) = lim;
            if (lim <= qa)
                goto found;
            cur = *(int *)(o + 0x340) + 1;
            *(int *)(o + 0x340) = cur;
        } while (cur < *(int *)(o + 0x84));
    found:
        if (!(*(int *)(o + 0x340) < *(int *)(o + 0x84)))
            return;
        *(s128 *)(o + 0x310) = *(s128 *)(w + 0x50);
        func_00047278(o, w, w + 0x60, w + 0x50);
    }
    func_00047C78(o);
    r = AI_GetRandomRange(0.3f, 0.6f);
    func_000479F0(o, o + 0x260, r, r * 3.1415925f / 20.0f, 20.0f);
}
#endif
