void iosMakeLightColorMatrix(float *dst, float *color0, float *color1, float *color2, float *ambient)
{
    __asm__ __volatile__(
                         "lq $6, 0x0(%1)\n"
                         "lq $7, 0x0(%2)\n"
                         "lq $8, 0x0(%3)\n"
                         "lq $9, 0x0(%4)\n"
                         "sq $6, 0x0(%0)\n"
                         "sq $7, 0x10(%0)\n"
                         "sq $8, 0x20(%0)\n"
                         "sq $9, 0x30(%0)\n"
                         :
                         : "r"(dst), "r"(color0), "r"(color1), "r"(color2), "r"(ambient)
                         : "$6", "$7", "$8", "$9", "memory");
}
