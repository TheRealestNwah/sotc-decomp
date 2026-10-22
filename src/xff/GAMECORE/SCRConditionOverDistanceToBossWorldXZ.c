extern char gcGlobalVar[];
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);

int SCRConditionOverDistanceToBossWorldXZ(void *actor, float dist)
{
    void *boss = SCRGetFirstObj(gcGlobalVar + 0x2B8);
    char *bossLayout;
    char *layout;
    float d;

    if (boss == 0)
        return 0;
    bossLayout = GetLayoutClass(boss);
    layout = GetLayoutClass(actor);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(*(float **)(bossLayout + 0x134)), "r"(*(float **)(layout + 0x134))
                         : "$2");
    return dist <= d;
}
