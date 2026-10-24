void iosCopyMatrix(float *dst, float *src)
{
    __asm__ __volatile__(
                         "lq $9, 0x30(%1)\n"
                         "sq $9, 0x30(%0)\n"
                         "lq $8, 0x20(%1)\n"
                         "sq $8, 0x20(%0)\n"
                         "lq $7, 0x10(%1)\n"
                         "sq $7, 0x10(%0)\n"
                         "lq $6, 0x0(%1)\n"
                         "sq $6, 0x0(%0)\n"
                         :
                         : "r"(dst), "r"(src)
                         : "$6", "$7", "$8", "$9", "memory");
}
