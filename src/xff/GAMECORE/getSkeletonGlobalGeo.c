typedef int s128 __attribute__((mode(TI)));

extern char *GetLayoutClass(void *);

typedef struct {
    void *actor;
    char pad4[0xC];
    char *skeleton;
    int index;
} SkeletonRef;

static inline char *skeletonNode(SkeletonRef *ref)
{
    return (char *)((ref->index << 6) + *(int *)(ref->skeleton + 8));
}

void getSkeletonGlobalGeo(s128 *out, SkeletonRef *ref)
{
    void *actor;
    char *node = skeletonNode(ref);

    actor = ref->actor;
    if (*(int *)(node + 0x38) == -1) {
        char *layout = GetLayoutClass(actor);
        s128 *q = (s128 *)(skeletonNode(ref) + 0x20);
        __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                             "lqc2 vf12, 0x0(%1)\n"
                             "vmul.xyzw vf13, vf11, vf12\n"
                             "vaddy.x vf13, vf13, vf13y\n"
                             "vaddz.x vf13, vf13, vf13z\n"
                             "vsubx.w vf13, vf13, vf13x\n"
                             "vmulw.xyz vf14, vf12, vf11w\n"
                             "vmulw.xyz vf15, vf11, vf12w\n"
                             "vopmula.xyz ACC, vf12, vf11\n"
                             "vopmsub.xyz vf16, vf11, vf12\n"
                             "vadd.xyz vf13, vf14, vf15\n"
                             "vadd.xyz vf13, vf13, vf16\n"
                             "sqc2 vf13, 0x0(%2)\n"
                             : : "r"(*(s128 **)(layout + 0x13C)), "r"(q), "r"(out) : "memory");
    } else {
        *out = *(s128 *)(node + 0x20);
    }
}
