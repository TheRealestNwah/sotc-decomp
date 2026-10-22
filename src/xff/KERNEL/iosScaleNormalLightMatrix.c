void iosScaleNormalLightMatrix(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf24, 0x0(%1)\n"
        "lqc2 vf25, 0x10(%1)\n"
        "lqc2 vf26, 0x20(%1)\n"
        "lqc2 vf27, 0x30(%1)\n"
        "lqc2 vf28, 0x0(%2)\n"
        "vmulx.xyz vf24, vf24, vf28x\n"
        "vmuly.xyz vf25, vf25, vf28y\n"
        "vmulz.xyz vf26, vf26, vf28z\n"
        "sqc2 vf24, 0x0(%0)\n"
        "sqc2 vf25, 0x10(%0)\n"
        "sqc2 vf26, 0x20(%0)\n"
        "sqc2 vf27, 0x30(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1), "r"(a2) : "memory");
}
