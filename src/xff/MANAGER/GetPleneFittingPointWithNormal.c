typedef int s128 __attribute__((mode(TI)));

extern float GetPointDistanceFromPlane(float *plane, float *p);

void GetPleneFittingPointWithNormal(float *out, float *plane, float *point, float *dir)
{
    float offset[4] __attribute__((aligned(16)));
    float dot;
    float t;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(plane), "r"(dir) : "$2");
    if (dot == 0.0f) {
        *(s128 *)out = *(s128 *)point;
        return;
    }
    t = -GetPointDistanceFromPlane(plane, point) / dot;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(offset), "r"(dir), "r"(t) : "memory");
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(point), "r"(offset) : "memory");
}
