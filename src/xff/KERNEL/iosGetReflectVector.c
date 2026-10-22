void iosGetReflectVector(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf4, 0x0(%1)\n"
        "lqc2 vf5, 0x0(%2)\n"
        "vmul.xyz vf7, vf4, vf5\n"
        "vaddy.x vf7, vf7, vf7y\n"
        "vaddz.x vf7, vf7, vf7z\n"
        "vadd.xyzw vf6, vf0, vf0\n"
        "vmulx.xyz vf5, vf5, vf7x\n"
        "vmulw.xyz vf5, vf5, vf6w\n"
        "vsub.xyz vf4, vf4, vf5\n"
        "sqc2 vf4, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1), "r"(a2) : "memory");
}
