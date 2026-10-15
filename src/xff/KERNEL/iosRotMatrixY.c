extern float UnitMatrix[];
extern void iosGetAlignSinCosf(float *, float);

void iosRotMatrixY(float *m, float a)
{
    float sc[2];
    float s, c;
    iosGetAlignSinCosf(sc, a);
    __asm__ __volatile__("lq $9, 0x30(%1)\n"
                         "sq $9, 0x30(%0)\n"
                         "lq $8, 0x20(%1)\n"
                         "sq $8, 0x20(%0)\n"
                         "lq $7, 0x10(%1)\n"
                         "sq $7, 0x10(%0)\n"
                         "lq $6, 0x0(%1)\n"
                         "sq $6, 0x0(%0)\n"
                         : : "r"(m), "r"(UnitMatrix) : "$6", "$7", "$8", "$9", "memory");
    s = sc[0];
    c = sc[1];
    m[0] = c;
    m[2] = -s;
    m[8] = s;
    m[10] = c;
}
