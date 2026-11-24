#ifdef NONMATCHING
/* Parked: 2 diffs (was 3): layout pinned to $3, priority to $4, the layout+0x134 load done in place by an asm lw on a $3-pinned copy, and the call arguments pinned to $a0, $a2, $a1 in that order. Remaining: the Original sets a0 (pos) before a1/a2 ahead of is_clear_camera_region_condition; ours sets a2 first. Chained empty-asm dependencies and other pin orders stayed at 2 or worse. */
typedef int s128 __attribute__((mode(TI)));
extern char *GetLayoutClass(int);
extern int is_clear_camera_region_condition(float *pos, void *region, void *arg, void *camera,
                                            int boss);
extern void *func_000E8F50(int type, unsigned long key);
extern void *B_0015E350[];

static inline float distanceSquare(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "lqc2 vf06, 0x0(%2)\n"
                         "vsub.xyzw vf07, vf05, vf06\n"
                         "vmul.xyz vf07, vf07, vf07\n"
                         "vaddy.x vf07, vf07, vf07y\n"
                         "vaddz.x vf07, vf07, vf07z\n"
                         "qmfc2 %0, vf07\n"
                         : "=r"(d) : "r"(a), "r"(b));
    return d;
}

void *get_apply_camera_region(int layoutId, int type, unsigned long key, void *arg, void *camera,
                              int boss)
{
    float pos[4] __attribute__((aligned(16)));
    int i;
    int bestPriority = 0;
    void *best;
    float bestDist = 3.4028235e38f;

    *(s128 *)pos = **(s128 **)(GetLayoutClass(layoutId) + 0x134);
    best = func_000E8F50(type, key);
    if (best)
        bestPriority = *(int *)(*(char **)((char *)best + 0x14) + 0x10);
    for (i = 0x31; i >= 0; i--) {
        char *region = B_0015E350[0x31 - i];
        char *entry;
        register char *layout __asm__("$3");
        register int priority __asm__("$4");
        float dist;
        if (!region)
            continue;
        layout = GetLayoutClass(*(int *)(region + 0x10));
        entry = *(char **)(region + 0x14);
        priority = *(int *)(entry + 0x10);
        if (priority < bestPriority)
            continue;
        {
            register char *l2 __asm__("$3") = layout;
            __asm__("lw %0, 0x134(%0)" : "+r"(l2));
            dist = distanceSquare(pos, (float *)l2);
        }
        if (region == arg) {
            dist -= 1.0f;
            if (dist < 0.0f)
                dist = 0.0f;
        }
        if (bestPriority < priority || dist < bestDist) {
            register float *pp __asm__("$4") = pos;
            register void *aa __asm__("$6") = arg;
            register char *rr __asm__("$5") = region;
            if (is_clear_camera_region_condition(pp, rr, aa, camera, boss) == 1) {
                bestPriority = *(int *)(entry + 0x10);
                best = region;
                bestDist = dist;
            }
        }
    }
    return best;
}
#else
extern void *get_apply_camera_region(int, int, unsigned long, void *, void *, int);
#endif
