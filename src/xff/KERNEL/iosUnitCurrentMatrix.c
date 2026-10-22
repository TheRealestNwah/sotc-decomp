void iosUnitCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vmove.xyzw vf4, vf0\n"
        "vmr32.xyzw vf3, vf4\n"
        "vmr32.xyzw vf2, vf3\n"
        "vmr32.xyzw vf1, vf2\n"
        ".set reorder\n"
        : : : "memory");
}
