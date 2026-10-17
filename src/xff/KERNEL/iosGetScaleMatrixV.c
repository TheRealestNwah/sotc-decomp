extern float UnitMatrix[];
void iosGetScaleMatrixV(float *m,float *scale)
{
    __asm__ __volatile__("lq $9, 0x30(%1)\n"
                         "sq $9, 0x30(%0)\n"
                         "lq $8, 0x20(%1)\n"
                         "sq $8, 0x20(%0)\n"
                         "lq $7, 0x10(%1)\n"
                         "sq $7, 0x10(%0)\n"
                         "lq $6, 0x0(%1)\n"
                         "sq $6, 0x0(%0)\n"
                         : : "r"(m), "r"(UnitMatrix) : "$6", "$7", "$8", "$9", "memory");
    m[0]=scale[0];
    m[5]=scale[1];
    m[10]=scale[2];
}
