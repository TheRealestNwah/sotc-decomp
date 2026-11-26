/* Parked at 10 diffs. Pinning opt to $s4 and moving the final transform into an inline helper
   (with the positions address as off + (int)positions) fix the s4/s5 swap and the last block.
   Remaining: the n loads use $v0 where the Original uses $v1, and the sll for off is scheduled
   before the inner loop invariants instead of after them. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

typedef struct {
    char pad0[0x15C];
    Vec4 (*matrices)[4];
    char pad160[0x34C - 0x160];
    Vec4 *positions;
    char pad350[0x358 - 0x350];
    int *options;
} Cls;

extern int GetMotionOptionNodeParentId(void *, int);
extern int GetCharacterClassOptionNodeLocalQuaternionPos(Vec4 *, Vec4 *, Cls *, int, int);

static inline void xformPos(void *dst, void *m, void *v)
{
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
                             : : "r"(dst), "r"(m), "r"(v) : "memory");
}

void func_00041488(Cls *c)
{
    Vec4 pos;
    Vec4 quat;
    Vec4 ppos;
    Vec4 pquat;
    volatile int n;
    register int *opt asm("$20");
    int i;
    int p;
    int off;

    n = 0;
    opt = c->options;
    if (opt)
        n = opt[8];
    for (i = 0; i < n; i++) {
        if (GetMotionOptionNodeParentId(opt, i) < 0)
            continue;
        p = GetMotionOptionNodeParentId(opt, i);
        GetCharacterClassOptionNodeLocalQuaternionPos(&quat, &pos, c, i, 1);
        off = i << 4;
        do {
            if (p <= 0 || !(p & 0x10000))
                break;
            p &= ~0x10000;
            GetCharacterClassOptionNodeLocalQuaternionPos(&pquat, &ppos, c, p, 1);
            __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                                 "lqc2 vf18, 0x0(%1)\n"
                                 "vmove.w vf18, vf0\n"
                                 "vaddw.xyz vf12, vf0, vf0w\n"
                                 "lqc2 vf11, 0x0(%2)\n"
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
                                 "vmaddw.xyzw vf10, vf18, vf8w\n"
                                 "sqc2 vf10, 0x0(%0)\n"
                                 : : "r"(&pos), "r"(&ppos), "r"(&pquat) : "memory");
            p = GetMotionOptionNodeParentId(opt, p);
        } while (1);
        xformPos((void *)(off + (int)c->positions), c->matrices[p], &pos);
    }
}
#endif
