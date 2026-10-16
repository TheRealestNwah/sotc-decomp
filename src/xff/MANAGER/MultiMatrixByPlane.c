#define VU_APPLY_MATRIX(dst, m, v) \
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n" \
                         "lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "vmulax.xyzw ACC, vf14, vf08x\n" \
                         "vmadday.xyzw ACC, vf15, vf08y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf08z\n" \
                         "vmaddw.xyzw vf10, vf17, vf08w\n" \
                         "sqc2 vf10, 0x0(%0)\n" \
                         : : "r"(dst), "r"(m), "r"(v) : "memory")
#define VU_INNER_PRODUCT(ret, a, b) \
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n" \
                         "lqc2 vf06, 0x0(%2)\n" \
                         "vaddw.x vf07, vf00, vf00w\n" \
                         "vmul.xyz vf06, vf05, vf06\n" \
                         "vaddax.x ACC, vf00, vf06x\n" \
                         "vmadday.x ACC, vf07, vf06y\n" \
                         "vmaddz.x vf06, vf07, vf06z\n" \
                         "qmfc2 $2, vf06\n" \
                         "mtc1 $2, %0\n" \
                         : "=f"(ret) : "r"(a), "r"(b) : "$2")

void MultiMatrixByPlane(float *out, char *m, float *plane)
{
    float d;
    VU_APPLY_MATRIX(out, m, plane);
    VU_INNER_PRODUCT(d, out, m + 0x30);
    out[3] = plane[3] - d;
}
