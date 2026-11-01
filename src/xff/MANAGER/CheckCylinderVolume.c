extern void iosInverseMatrix(float *, float *);

int CheckCylinderVolume(float *matrix, float *point, float *bounds)
{
    float inv[16] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    float radial;
    int inside;
    int result;

    iosInverseMatrix(inv, matrix);
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
                         : : "r"(local), "r"(inv), "r"(point) : "memory");

    inside = 0;
    if (bounds[1] <= local[1] && local[1] <= bounds[2])
        inside = 1;
    result = 0;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf7, 0(%1)\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         ".set reorder\n"
                         : "=f"(radial) : "r"(local) : "$2");
    if (radial < bounds[0] * bounds[0])
        result = inside != 0;
    return result;
}
