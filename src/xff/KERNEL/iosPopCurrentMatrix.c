void iosPopCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vlqd.xyzw vf4, (--vi15)\n"
        "vlqd.xyzw vf3, (--vi15)\n"
        "vlqd.xyzw vf2, (--vi15)\n"
        "vlqd.xyzw vf1, (--vi15)\n"
        ".set reorder\n"
        : : : "memory");
}
