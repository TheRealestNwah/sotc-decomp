typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char ZUnitVectorInv[];
extern char gcGlobalVar[];
extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern void func_000B0F90(char *);
extern void AI_GetSmallAnimalAIParam(void *, void *, void *, void *, void *, void *);

static inline void quatRotateVector(Vec4 *out0, float *quat0, Vec4 *vec0)
{
    register Vec4 *vec __asm__("$2") = vec0;
    register Vec4 *out __asm__("$4") = out0;
    register float *quat __asm__("$3") = quat0;
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         : : "r"(vec), "r"(quat));
    __asm__ __volatile__("sqc2 vf10, 0x0(%0)\n" : : "r"(out) : "memory");
}


#ifdef NONMATCHING /* 7 diffs: the ndir copy goes through $s1 base instead of base+0x170($s5), and the length/divide pair uses $f0/$f1 swapped */
static void func_000B1128(char *m)
{
    char sp[0x10] __attribute__((aligned(16)));
    int th = isysGetThisSubThread();
    char *lc = GetLayoutClass(th);
    char *tl = GetLayoutClass(*(int *)(m + 0x44));
    char *cc = GetCharacterClass(th);
    char *ndir;
    char *conj;
    char *dirq;
    float g;
    float len;
    char *gp;

    func_000B0F90(m);
    *(int *)(m + 0x1D8) = 0;
    *(int *)(m + 0x1A0) = 0x27;
    quatRotateVector((Vec4 *)(m + 0x160), (float *)*(char **)(lc + 0x13C), (Vec4 *)ZUnitVectorInv);
    ndir = m + 0x170;
    *(s128 *)(m + 0x170) = *(s128 *)(m + 0x160);
    __asm__ __volatile__("" : : : "memory");
    *(int *)(m + 0x174) = 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(ndir) : "memory");
    conj = m + 0x180;
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%1)\n"
                         : : "r"(*(char **)(lc + 0x13C)), "r"(conj) : "memory");
    dirq = m + 0x160;
    AI_GetSmallAnimalAIParam(m + 0x50, *(char **)(tl + 0x134), *(char **)(lc + 0x134), conj, dirq, ndir);
    AI_GetSmallAnimalAIParam(m + 0xB0, m + 0x20, *(char **)(lc + 0x134), conj, dirq, ndir);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(sp), "r"(m + 0x150), "r"(*(char **)(tl + 0x134)) : "memory");
    gp = gcGlobalVar;
    g = *(float *)(gp + 0x190);
    if (0.0f < g) {
        float inv = 1.0f / g;
        __asm__ __volatile__("mfc1 $2, %2\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni $2, vf6\n"
                             "vmulx.xyzw vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf7, 0x0(%1)\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             ".word 0x4BA703BD\n"
                             "vwaitq\n"
                             "cfc2.ni $2, $vi22\n"
                             "mtc1 $2, %0\n"
                             : "=f"(len) : "r"(sp), "f"(inv) : "$2", "memory");
        *(float *)(m + 0x140) = len;
        *(float *)(m + 0x148) = (len - *(float *)(m + 0x144)) / *(float *)(gp + 0x190);
    }
    *(float *)(m + 0x1A4) = *(float *)(*(char **)(cc + 0x1140) + 0x44);
}
#endif
