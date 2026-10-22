void getZ(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf1, 0x0(%1)\n"
        "lqc2 vf24, 0x0(%2)\n"
        "lqc2 vf25, 0x10(%2)\n"
        "lqc2 vf26, 0x20(%2)\n"
        "lqc2 vf27, 0x30(%2)\n"
        "vmulax.xyzw ACC, vf24, vf1x\n"
        "vmadday.xyzw ACC, vf25, vf1y\n"
        "vmaddaz.xyzw ACC, vf26, vf1z\n"
        "vmaddw.xyzw vf28, vf27, vf0w\n"
        "vmr32.y vf28, vf28\n"
        "vmr32.x vf28, vf28\n"
        "vaddw.x vf28, vf28, vf1w\n"
        "vsubw.z vf28, vf28, vf1w\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "sqc2 vf28, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1), "r"(a2) : "memory");
}
