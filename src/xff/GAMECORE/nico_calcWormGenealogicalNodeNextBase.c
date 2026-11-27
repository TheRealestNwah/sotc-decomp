typedef int s128 __attribute__((mode(TI)));

extern int D_0017B8C8;
extern char *GetSCRCharaAIWorkPtr(int);
extern char *GetLayoutClass(int);
extern int func_00128510(void *, void *, float, void *, void *);
extern void func_00128D00(float, void *, void *, void *, void *, void *, void *, void *);

static inline void quatMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

#ifdef NONMATCHING /* 35 diffs, same size: the sqrt operand pins m+0x10 to $2, the index to $3 and the address to $3, which matches the first asm argument setup; the m+8/m+4/m+0xC element addresses are written as array indexing (shift first in the addu, like the Original), and a memory barrier between the two else-branch copies keeps the second copy's loads after the first store. Remaining: register numbering of the index arithmetic around the two func_00128D00 calls and in the asm argument setup */
void nico_calcWormGenealogicalNodeNextBase(char *m)
{
    char sp[0x20] __attribute__((aligned(16)));
    int s2 = *(int *)m;
    char *wk = (char *)(((int)GetSCRCharaAIWorkPtr(s2) + 0x41B3) & ~0xF);
    char *lay, *e;
    float len;

    if (*(signed char *)(wk + 0x1298) != 0) {
        register char *b10 __asm__("$2") = *(char **)(m + 0x10);
        register int ix __asm__("$3") = *(int *)(m + 0x14);
        register char *src __asm__("$3");
        src = *(char **)(b10 + 8) + (ix << 6) + 0x10;
        __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             ".word 0x4BA703BD\n"
                             "vwaitq\n"
                             "cfc2.ni $2, $vi22\n"
                             "mtc1 $2, %0\n"
                             : "=f"(len) : "r"(src) : "$2");
        lay = GetLayoutClass(s2);
        if (func_00128510(sp, sp + 0x10, len * *(float *)(lay + 0x98), wk + 0x12A0, wk + D_0017B8C8 * 0x50 + 0x10)) {
            e = wk + D_0017B8C8 * 0x50;
            func_00128D00(180.0f, e + 0x10, m, e - 0x40,
                          (char *)&((char (*)[0x40])*(char **)(m + 8))[*(int *)(m + 0x14)] + 0x30,
                          wk + D_0017B8C8 * 0x10 + 0xA10, sp, sp + 0x10);
        } else {
            e = wk + D_0017B8C8 * 0x50;
            func_00128D00(*(float *)(e + 0x40), e + 0x10, m, e - 0x40,
                          (char *)&((char (*)[0x40])*(char **)(m + 8))[*(int *)(m + 0x14)] + 0x30,
                          wk + D_0017B8C8 * 0x10 + 0xA10, e + 0x60, 0);
        }
        quatMul(wk + D_0017B8C8 * 0x10 + 0xA20, wk + D_0017B8C8 * 0x10 + 0xA10, (char *)&((s128 *)*(char **)(m + 4))[*(int *)(m + 0x14)]);
        __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                             "vmul.xyzw vf15, vf14, vf14\n"
                             "vaddy.x vf15, vf15, vf15y\n"
                             "vaddz.x vf15, vf15, vf15z\n"
                             "vaddw.x vf15, vf15, vf15w\n"
                             "vrsqrt Q, vf0w, vf15x\n"
                             "vwaitq\n"
                             "vmulq.xyzw vf15, vf14, Q\n"
                             "sqc2 vf15, 0x0(%0)\n"
                             : : "r"(wk + D_0017B8C8 * 0x10 + 0xA20) : "memory");
    } else {
        *(s128 *)(wk + D_0017B8C8 * 0x50 + 0x10) = *(s128 *)((char *)&((char (*)[0x40])*(char **)(m + 8))[*(int *)(m + 0x14)] + 0x30);
        __asm__ __volatile__("" ::: "memory");
        *(s128 *)(wk + D_0017B8C8 * 0x10 + 0xA20) = *(s128 *)((char *)&((s128 *)*(char **)(m + 0xC))[*(int *)(m + 0x14)]);
    }
}
#endif
