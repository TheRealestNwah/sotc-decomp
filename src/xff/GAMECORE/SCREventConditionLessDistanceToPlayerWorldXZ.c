extern int *DldSysUndefSymbol;
extern int *getSScriptWork(void *);
extern char *GetLayoutClass(void *);

int SCREventConditionLessDistanceToPlayerWorldXZ(void *actor, int a1, int a2, int a3, int a4, int a5, int a6,
                                                 unsigned int *h, float dist)
{
    int *w = getSScriptWork(actor);
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    int *o = (t != 0 && t != DldSysUndefSymbol) ? (int *)t[4] : 0;
    float d;

    if (*w == 0 || o == 0 || o[2] == 0)
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d)
                         : "r"(*(float **)(GetLayoutClass((void *)o[2]) + 0x134)), "r"(*(float **)(w[1] + 0x134))
                         : "$2");
    return d <= dist;
}
