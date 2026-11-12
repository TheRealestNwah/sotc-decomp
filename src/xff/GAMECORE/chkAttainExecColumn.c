typedef int s128 __attribute__((mode(TI)));
extern void StabilizeToYRotQuaternion(void *);

#ifdef NONMATCHING /* 4 diffs: otherwise exact (VU blocks, pinned registers; the empty asm on pp fixes the load/addiu order). The matrix pointer for the inverse ($v1) is copied from $v0 instead of a fresh addiu (asm barriers on mA/m do not help), and the final return flag uses the opposite branch polarity (tried ternary, flag variable, goto and inverted forms) */
static int chkAttainExecColumn(char *w0, float *pos0, char *cam0, char *src)
{
    register char *w __asm__("$17") = w0;
    register float *pos __asm__("$16") = pos0;
    register char *cam __asm__("$18") = cam0;
    char q[0x10] __attribute__((aligned(16)));
    char mtx[0x40] __attribute__((aligned(16)));
    float res[4] __attribute__((aligned(16)));
    register char *m __asm__("$3");
    register int t0 __asm__("$8"), t1 __asm__("$9"), t2 __asm__("$10"), t3 __asm__("$11"), t4 __asm__("$12"), t5 __asm__("$13"), t6 __asm__("$14"), t7 __asm__("$15");
    register char *mA __asm__("$2");
    register char *pp __asm__("$4");
    float dot;
    float y;
    float lim;

    __asm__("" : "+r"(w), "+r"(pos), "+r"(cam));
    *(s128 *)q = *(s128 *)(src + 0x470);
    if (*(int *)(w + 0xE8) != 0)
        StabilizeToYRotQuaternion(q);
    pp = *(char **)(cam + 0x134);
    __asm__("" : "+r"(pp));
    mA = mtx;
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
                         "lqc2 vf4, 0x0(%2)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(mA), "r"(q), "r"(pp) : "memory");
    m = mtx;
    __asm__ __volatile__("lqc2 vf24, 0x30(%8)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq %0, 0x0(%8)\n"
                         "lq %1, 0x10(%8)\n"
                         "lq %2, 0x20(%8)\n"
                         "qmfc2.ni %3, vf0\n"
                         "pextlw %4, %1, %0\n"
                         "pextuw %5, %1, %0\n"
                         "pextlw %6, %3, %2\n"
                         "pextuw %7, %3, %2\n"
                         "pcpyld %0, %6, %4\n"
                         "pcpyud %1, %4, %6\n"
                         "pcpyld %2, %7, %5\n"
                         "pcpyud %3, %5, %7\n"
                         "qmtc2.ni %0, vf24\n"
                         "qmtc2.ni %1, vf25\n"
                         "qmtc2.ni %2, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%8)\n"
                         "sqc2 vf25, 0x10(%8)\n"
                         "sqc2 vf26, 0x20(%8)\n"
                         "sqc2 vf29, 0x30(%8)\n"
                         : "=&r"(t0), "=&r"(t1), "=&r"(t2), "=&r"(t3), "=&r"(t4), "=&r"(t5), "=&r"(t6), "=&r"(t7)
                         : "r"(m) : "memory");
    pos[3] = 1.0f;
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf14, 0x0(%2)\n"
                         "lqc2 vf15, 0x10(%2)\n"
                         "lqc2 vf16, 0x20(%2)\n"
                         "lqc2 vf17, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(res), "r"(pos), "r"(m) : "memory");
    y = res[1];
    res[1] = 0.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(res) : "$2");
    lim = *(float *)(w + 0x3CC);
    if (dot <= lim * lim) {
        if (__builtin_fabsf(y) <= *(float *)(w + 0x3D0))
            goto one;
        return 0;
    }
one:
    return 1;
}
#endif
