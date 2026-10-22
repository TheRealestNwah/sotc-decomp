extern void iosGetSinCosf(float *, float);

void iosGetRotYVector(void *destination, void *source, float angle)
{
    float matrix[16] __attribute__((aligned(16)));
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(".set noreorder\n"
                         "vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         ".set reorder\n");
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "mfc1 $9, %1\n"
                         "qmtc2.ni $8, vf5\n"
                         "qmtc2.ni $9, vf6\n"
                         "vaddx.x vf14, vf0, vf5x\n"
                         "vaddx.x vf16, vf0, vf6x\n"
                         "vsubx.z vf14, vf0, vf6x\n"
                         "vaddx.z vf16, vf0, vf5x\n"
                         "sqc2 vf14, 0(%2)\n"
                         "sqc2 vf15, 16(%2)\n"
                         "sqc2 vf16, 32(%2)\n"
                         "sqc2 vf17, 48(%2)\n"
                         ".set reorder\n"
                         : : "f"(sc[0]), "f"(sc[1]), "r"(matrix)
                         : "$8", "$9", "memory");
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(destination), "r"(matrix), "r"(source)
                         : "memory");
}

