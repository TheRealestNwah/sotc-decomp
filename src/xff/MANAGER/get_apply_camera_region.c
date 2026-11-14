#ifdef NONMATCHING
/* Parked: 9 diffs (register allocation: original keeps the layout pointer in v1 and the priority in a0; ours swaps them, and the qmfc2 result goes to a0 instead of v0). */
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
        char *layout;
        int priority;
        float dist;
        if (!region)
            continue;
        layout = GetLayoutClass(*(int *)(region + 0x10));
        entry = *(char **)(region + 0x14);
        priority = *(int *)(entry + 0x10);
        if (priority < bestPriority)
            continue;
        dist = distanceSquare(pos, *(float **)(layout + 0x134));
        if (region == arg) {
            dist -= 1.0f;
            if (dist < 0.0f)
                dist = 0.0f;
        }
        if (bestPriority < priority || dist < bestDist) {
            if (is_clear_camera_region_condition(pos, region, arg, camera, boss) == 1) {
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
