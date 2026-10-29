extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *list);
extern char *GetLayoutClass(void *object);
extern char *GetCharacterClass(void *object);
extern float GetWeaponRange(void);

static inline float distanceXYZ(float *a, float *b)
{
    float distance;
    __asm__ __volatile__(
        "lqc2 vf5, 0(%1)\n" "lqc2 vf6, 0(%2)\n"
        "vsub.xyzw vf7, vf5, vf6\n" "vmul.xyz vf7, vf7, vf7\n"
        "vmulax.w ACC, vf0, vf7x\n" "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n" "vsqrt Q, vf7w\n"
        "vwaitq\n" "cfc2 $2, $vi22\n" "mtc1 $2, %0\n"
        : "=f"(distance) : "r"(a), "r"(b) : "$2");
    return distance;
}

int isWeaponTargetReady(void *object)
{
    void *target = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    char *targetLayout;
    char *layout;
    float distance;
    if (target == 0) goto fail;
    targetLayout = GetLayoutClass(target);
    layout = GetLayoutClass(object);
    distance = distanceXYZ(*(float **)(targetLayout + 0x134), *(float **)(layout + 0x134));
    if (distance < GetWeaponRange()) goto success;
    if (!(*(unsigned long *)(GetCharacterClass(object) + 0x690) & 1UL)) goto fail;
success:
    return 1;
fail:
    return 0;
}
