void iosClearTransCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vmove.xyzw vf4, vf0\n"
        ".set reorder\n"
        : : : "memory");
}
