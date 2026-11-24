typedef struct { long long x, y; } Pair;
typedef float Vec4[4] __attribute__((aligned(16)));

extern int D_0017B8C4;
extern Pair RO_00181790;
extern char *GetCharacterClass(int);
extern void nico_calcTailGenealogicalNodeNext(void *);

/* Parked: 10 diffs (same size, 81 words). An empty asm on e and copying
 * the pair high word first take it from 15. Remaining: the Original forms
 * the RO_00181790 address (lui $a0) before the D_0017B8C4 one (lui $a1) and
 * loads D after ik; ours swaps those registers and loads D first, and the
 * same a0/a1 swap shows at the final &D_0017B8C4 / &L.v pair. */
#ifdef NONMATCHING
static inline void mkmat(float *mm, char *q, char *t)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
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
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(mm), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(mm), "r"(t));
}

void nico_calcTailGenealogicalNodeTail(int *obj)
{
    struct { Vec4 mat[4]; Pair v; } L;
    char *ik = *(char **)(GetCharacterClass(*obj) + 0x1118);
    char *e;
    int *pd;
    float *m = L.mat[0];

    e = (char *)((D_0017B8C4 << 4) + (int)ik);
    __asm__("" : "+r"(e));
    L.v.y = RO_00181790.y;
    L.v.x = RO_00181790.x;
    mkmat(m, e, e + 0x280);
    pd = &D_0017B8C4;
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"((char *)((*pd << 4) + (int)ik) + 0x290), "r"(L.mat), "r"(&L.v) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"((char *)((*pd << 4) + (int)ik) + 0x10) : "memory");
    nico_calcTailGenealogicalNodeNext(obj);
    *(int *)(ik + 0x3C0) = 1;
}
#else
extern void nico_calcTailGenealogicalNodeTail(int *obj);
#endif
