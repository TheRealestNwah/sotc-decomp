typedef int s128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));

void iosSetCameraMatrix(float *out, float *pos, float *dir, float *up)
{
    struct { Vec4 m[4]; Vec4 t; } L;

    __asm__ __volatile__("vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         "sqc2 vf17, 0x30(%0)\n"
                         : : "r"(L.m[0]) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         "lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         : : "r"(L.t), "r"(L.m[0]), "r"(up), "r"(dir) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(L.m[2]), "r"(dir) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(L.m[1]), "r"(L.m[2]), "r"(L.m[0]) : "memory");
    *(s128 *)L.m[3] = *(s128 *)pos;
    __asm__ __volatile__("lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "lqc2 vf1, 0x30(%1)\n"
                         "vmove.xyzw vf2, vf1\n"
                         "vsub.xyz vf1, vf1, vf1\n"
                         "vmove.xyzw vf9, vf1\n"
                         "qmfc2.ni $11, vf1\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "qmtc2.ni $8, vf3\n"
                         "qmtc2.ni $9, vf4\n"
                         "qmtc2.ni $10, vf8\n"
                         "vmulax.xyz ACC, vf3, vf2x\n"
                         "vmadday.xyz ACC, vf4, vf2y\n"
                         "vmaddz.xyz vf1, vf8, vf2z\n"
                         "vsub.xyz vf1, vf9, vf1\n"
                         "sq $8, 0x0(%0)\n"
                         "sq $9, 0x10(%0)\n"
                         "sq $10, 0x20(%0)\n"
                         "sqc2 vf1, 0x30(%0)\n"
                         : : "r"(out), "r"(L.m[0])
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}
