typedef int s128 __attribute__((mode(TI)));

extern char *GetLayoutClass(int);
extern void iosTransMatrixF(void *, int, float, float, float);

static inline float sqrtF(float x)
{
    __asm__ __volatile__("sqrt.s %0, %0" : "+f"(x));
    return x;
}

static int func_00081670(void *out, int layout)
{
    char inv[0x40] __attribute__((aligned(16)));
    char mtx0[0x40] __attribute__((aligned(16)));
    char res[0x10] __attribute__((aligned(16)));
    register char *mtx __asm__("$17");
    register int ok __asm__("$18");
    float d2;
    float scale;
    
    register int t0 __asm__("$8"), t1 __asm__("$9"), t2 __asm__("$10"), t3 __asm__("$11"), t4 __asm__("$12"), t5 __asm__("$13"), t6 __asm__("$14"), t7 __asm__("$15");

    {
        char *lc = GetLayoutClass(layout);
        ok = 0;
        mtx = mtx0;
        iosTransMatrixF(mtx, *(int *)(lc + 0x158) + 0x600, 0.15f, 0.0f, 0.0f);
    }
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
                         "sqc2 vf24, 0x0(%9)\n"
                         "sqc2 vf25, 0x10(%9)\n"
                         "sqc2 vf26, 0x20(%9)\n"
                         "sqc2 vf29, 0x30(%9)\n"
                         : "=&r"(t0), "=&r"(t1), "=&r"(t2), "=&r"(t3), "=&r"(t4), "=&r"(t5), "=&r"(t6), "=&r"(t7)
                         : "r"(mtx), "r"(inv) : "memory");
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf14, 0x0(%2)\n"
                         "lqc2 vf15, 0x10(%2)\n"
                         "lqc2 vf16, 0x20(%2)\n"
                         "lqc2 vf17, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%3)\n"
                         "lqc2 vf7, 0x0(%3)\n"
                         "vmul.xy vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d2) : "r"(out), "r"(inv), "r"(res) : "$2", "memory");
    if (d2 < 0.03239999f) {
        scale = 0.17999998f / sqrtF(d2);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                             "mfc1 %0, %4
"
                             "qmtc2.ni %0, vf6\n"
                             "vmulx.xy vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf8, 0x0(%1)\n"
                             "lqc2 vf14, 0x0(%2)\n"
                             "lqc2 vf15, 0x10(%2)\n"
                             "lqc2 vf16, 0x20(%2)\n"
                             "lqc2 vf17, 0x30(%2)\n"
                             "vmulax.xyzw ACC, vf14, vf8x\n"
                             "vmadday.xyzw ACC, vf15, vf8y\n"
                             "vmaddaz.xyzw ACC, vf16, vf8z\n"
                             "vmaddw.xyzw vf10, vf17, vf8w\n"
                             "sqc2 vf10, 0x0(%3)\n"
                             : "=&r"(t0) : "r"(res), "r"(mtx), "r"(out), "f"(scale) : "memory");
        ok = 1;
    }
    return ok;
}
