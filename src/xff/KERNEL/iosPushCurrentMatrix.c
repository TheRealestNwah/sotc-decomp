void iosPushCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vsqi.xyzw vf1, (vi15++)\n"
        "vsqi.xyzw vf2, (vi15++)\n"
        "vsqi.xyzw vf3, (vi15++)\n"
        "vsqi.xyzw vf4, (vi15++)\n"
        ".set reorder\n"
        : : : "memory");
}
