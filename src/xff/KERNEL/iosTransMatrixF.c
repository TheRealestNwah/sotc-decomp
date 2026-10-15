static inline void transMatrix(float *out, float *m, float *v)
{
    __asm__ __volatile__("lq $9, 0x30(%1)\n"
                         "sq $9, 0x30(%0)\n"
                         "lq $8, 0x20(%1)\n"
                         "sq $8, 0x20(%0)\n"
                         "lq $7, 0x10(%1)\n"
                         "sq $7, 0x10(%0)\n"
                         "lq $6, 0x0(%1)\n"
                         "sq $6, 0x0(%0)\n"
                         : : "r"(out), "r"(m) : "$6", "$7", "$8", "$9", "memory");
    out += 12;
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf08x\n"
                         "vmadday.xyzw ACC, vf15, vf08y\n"
                         "vmaddaz.xyzw ACC, vf16, vf08z\n"
                         "vmaddw.xyzw vf10, vf17, vf08w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

void iosTransMatrixF(float *out, float *m, float x, float y, float z)
{
    float v[4] __attribute__((aligned(16)));
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
    transMatrix(out, m, v);
}
