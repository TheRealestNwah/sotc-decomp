extern void iosAbsVector(void *, void *);
extern void iosInverseMatrix(float *, void *);

int CheckCubeVolume(void *matrix, float *point, float *bounds)
{
    float inverse[16] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    int result;

    iosInverseMatrix(inverse, matrix);

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
                         : : "r"(local), "r"(inverse), "r"(point) : "memory");
    iosAbsVector(local, local);
    result = 0;
    if (local[0] <= bounds[0] && local[1] <= bounds[1] && local[2] <= bounds[2])
        result = 1;
    return result;
}
