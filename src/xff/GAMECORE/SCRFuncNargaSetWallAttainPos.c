typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

static inline void scale(Vec4 *o, Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(v), "r"(s) : "memory");
}

static inline void add(Vec4 *o, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vadd.xyz vf05, vf05, vf06\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(a), "r"(b) : "memory");
}
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern char *GetLayoutClass(void *);
extern void setAttainmentPosAndLock(char *, Vec4 *);

void SCRFuncNargaSetWallAttainPos(void *a, float s)
{
    Vec4 p;
    char *ai = GetSCRCharaAIWorkPtr(a);
    char *w = getSCRDataCtrlWork(a);
    char *l = GetLayoutClass(a);
    scale(&p, (Vec4 *)(ai + 0x5A90), s);
    add(&p, &p, *(Vec4 **)(l + 0x134));
    p.f[3] = 1.0f;
    setAttainmentPosAndLock(w, &p);
}
