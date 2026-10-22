extern void GetPlaneFittingPointForUnnormalizedPlane(float *, float *, float *);

void GetCollisionDynamicsProjectionFloatPosition(float *out, char *collision,
                                                  float *point, float distance)
{
    float projection[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float *plane = (float *)(collision + 0x10);
    unsigned int bits;

    GetPlaneFittingPointForUnnormalizedPlane(projection, plane, point);
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(normal), "r"(plane) : "memory");
    __asm__ __volatile__("mfc1 %0, %1\n" : "=r"(bits) : "f"(distance));
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(normal), "r"(bits) : "memory");
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(projection), "r"(normal) : "memory");
}
