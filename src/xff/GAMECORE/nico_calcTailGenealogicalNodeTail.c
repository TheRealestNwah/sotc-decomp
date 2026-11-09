typedef struct { long long x, y; } Pair;
typedef float Vec4[4] __attribute__((aligned(16)));

extern int D_0017B8C4;
extern Pair RO_00181790;
extern char *GetCharacterClass(int);
extern void nico_calcTailGenealogicalNodeNext(void *);

/* Parked: ~51 words differ (D_0017B8C4 address/index folding and the order of the RO pair copy and matrix pointer setup; size matches at 81 words). */
#ifdef NONMATCHING
void nico_calcTailGenealogicalNodeTail(int *obj)
{
    struct { Vec4 mat[4]; Pair v; } L;
    char *ik = *(char **)(GetCharacterClass(*obj) + 0x1118);
    char *e;
    int *pd;
    float *m = L.mat[0];

    e = ik + (D_0017B8C4 << 4);
    L.v = RO_00181790;
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
                         : : "r"(m), "r"(e) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(m), "r"(e + 0x280) : "memory");
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
                         : : "r"(ik + (*pd << 4) + 0x290), "r"(m), "r"(&L.v) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(ik + (*pd << 4) + 0x10) : "memory");
    nico_calcTailGenealogicalNodeNext(obj);
    *(int *)(ik + 0x3C0) = 1;
}
#else
extern void nico_calcTailGenealogicalNodeTail(int *obj);
#endif
