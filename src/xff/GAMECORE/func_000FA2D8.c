typedef int s128 __attribute__((mode(TI)));

extern char *getPointDataByAreaIdx();
extern float RO_001812F0;

#ifdef NONMATCHING /* 115 diffs: 12-argument candidate scorer; prologue and pinned $s0..$fp match, but ours spills only t2 to 0x20 where the original spills a3 to 0x20 and t2 to 0x24 (and reloads them), shifting every later offset */
static void func_000FA2D8(char *cam0, int a10, int a20, int a3, int *cntA0, int *cntB0, int *cntC, int *cnt0, int *flag0, char *vb0, char *va, float *best0)
{
    register char *cam __asm__("$18") = cam0;
    register int a1 __asm__("$20") = a10;
    register int a2 __asm__("$30") = a20;
    register int *cntA __asm__("$21") = cntA0;
    register int *cntB __asm__("$23") = cntB0;
    register int *cnt __asm__("$17") = cnt0;
    register int *flag __asm__("$19") = flag0;
    register char *vb __asm__("$16") = vb0;
    register float *best __asm__("$22") = best0;
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float dot;
    char *pd;
    int sp20 = a3;
    int *sp24 = cntC;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(va), "r"(vb) : "memory");
    pd = getPointDataByAreaIdx();
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(e), "r"(pd), "r"(vb) : "memory");
    if (*(int *)(cam + 0xEC) != 0) {
        d[1] = 0.0f;
        e[1] = 0.0f;
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(e) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(d), "r"(e) : "$2");
    if (dot <= *(float *)(cam + 0x3B0)) {
        if (*flag != 0) {
            *cnt = 0;
            *flag = 0;
        }
        cntA[*cnt] = a1;
        cntB[*cnt] = sp20;
        sp24[*cnt] = a2;
        *cnt += 1;
        *flag = 0;
        *best = RO_001812F0;
    } else if (*cnt == 0 || (*flag != 0 && dot < *best)) {
        *cnt = 0;
        cntA[0] = a1;
        cntB[*cnt] = sp20;
        sp24[*cnt] = a2;
        *best = dot;
        *cnt += 1;
        *flag = 1;
    }
}
#endif
