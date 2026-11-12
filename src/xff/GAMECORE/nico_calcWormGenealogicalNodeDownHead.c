typedef int s128 __attribute__((mode(TI)));

extern int D_0017B8C8;
extern int D_0017B8CC;
extern char *GetSCRCharaAIWorkPtr(int);
extern char *GetCharacterClass(int);
extern void func_00129E10(void *, void *, int, void *, void *, void *, int);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);
extern void GetMotionMatrix(int, int, int, int, int, int);
extern void nico_calcWormGenealogicalNodeHeadBase(void *);

#ifdef NONMATCHING /* 58 diffs: structure, VU blocks and call arguments match; the array-index address arithmetic (stride 0x50/0x10) is scheduled differently and the original reloads the counter each time */
void nico_calcWormGenealogicalNodeDownHead(char *m)
{
    char sp[0x20] __attribute__((aligned(16)));
    int s2 = *(int *)m;
    char *wk = (char *)(((int)GetSCRCharaAIWorkPtr(s2) + 0x41B3) & ~0xF);
    char *cc;
    char *e;
    int idx;

    *(char *)(wk + 0x129B) = 1;
    D_0017B8C8 = 0;
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(sp), "r"(wk + 0xA20) : "memory");
    if (*(signed char *)(wk + 0x129A) == 0) {
        cc = GetCharacterClass(s2);
        idx = D_0017B8C8;
        e = wk + idx * 0x50;
        *(s128 *)(wk + idx * 0x10 + 0xC20) = *(s128 *)(e + 0x10);
        *(s128 *)(wk + D_0017B8C8 * 0x50 + 0x10) = *(s128 *)(*(char **)(m + 8) + (*(int *)(m + 0x14) << 6) + 0x30);
        func_00129E10(e + 0x70, m, s2, wk, wk, cc, 1);
        idx = D_0017B8C8;
        e = wk + idx * 0x50;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(sp + 0x10), "r"(e + 0x10), "r"(e + 0x60) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(sp + 0x10) : "memory");
        GetQuaternionByAxisDirZY((char *)*(int *)(m + 4) + *(int *)(m + 0x14) * 0x10, sp + 0x10, sp);
        GetMotionMatrix(*(int *)(m + 8), *(int *)(m + 0xC), *(int *)(m + 0x10), *(int *)(m + 4), *(int *)(m + 0xB4), *(int *)(m + 0xB8));
        *(s128 *)(wk + D_0017B8C8 * 0x10 + 0xA20) = *(s128 *)((char *)*(int *)(m + 4) + *(int *)(m + 0x14) * 0x10);
        e = wk + D_0017B8C8 * 0x10 + 0xA20;
        __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                             "vmul.xyzw vf15, vf14, vf14\n"
                             "vaddy.x vf15, vf15, vf15y\n"
                             "vaddz.x vf15, vf15, vf15z\n"
                             "vaddw.x vf15, vf15, vf15w\n"
                             "vrsqrt Q, vf0w, vf15x\n"
                             "vwaitq\n"
                             "vmulq.xyzw vf15, vf14, Q\n"
                             "sqc2 vf15, 0x0(%0)\n"
                             : : "r"(e) : "memory");
        D_0017B8CC = 0;
        D_0017B8C8 += 1;
        return;
    }
    nico_calcWormGenealogicalNodeHeadBase(m);
    D_0017B8C8 += 1;
}
#endif
