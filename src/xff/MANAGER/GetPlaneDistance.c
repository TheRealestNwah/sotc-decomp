float GetPlaneDistance(void *point, void *plane)
{
    float distance;

    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vmul.xyz vf7, vf5, vf6\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vaddw.x vf7, vf7, vf6w\n"
                         "qmfc2.ni %0, vf7\n"
                         ".set reorder\n"
                         : "=r"(distance) : "r"(point), "r"(plane));
    return distance;
}
