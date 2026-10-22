typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
static Vec4 D_00136B10 = { 0 };
void charrootdyn_getOffsetGlobalPos(Vec4 *out, char *chara, float z, float x)
{
    Vec4 matrix[4];
    float *m = matrix[0].f;
    __asm__ __volatile__(".set noreorder\n"
        "vaddw.xyz vf12, vf0, vf0w\n"
        "lqc2 vf11, 0x0(%0)\n"
        "vmr32.w vf14, vf0\n"
        "vmr32.w vf15, vf0\n"
        "vmr32.w vf16, vf0\n"
        "vopmula.xyz ACC, vf11, vf12\n"
        "vmadd.xyz vf11, vf0, vf0\n"
        "vmadd.xyz vf10, vf11, vf12\n"
        "vmul.xyz vf13, vf11, vf10\n"
        "vopmula.xyz ACC, vf11, vf10\n"
        "vmaddw.xyz vf15, vf10, vf11w\n"
        "vmsubw.xyz vf16, vf10, vf11w\n"
        "vopmula.xyz ACC, vf13, vf12\n"
        "vmadd.xyz vf17, vf13, vf12\n"
        "vopmula.xyz ACC, vf15, vf12\n"
        "vmadd.xyz vf15, vf0, vf0\n"
        "vsub.xyz vf14, vf12, vf17\n"
        "vmove.yz vf17, vf14\n"
        "vmove.y vf14, vf16\n"
        "vmove.y vf16, vf15\n"
        "vmove.y vf15, vf17\n"
        "vmove.z vf14, vf15\n"
        "vmove.z vf15, vf16\n"
        "vmove.z vf16, vf17\n"
        "sqc2 vf14, 0x0(%1)\n"
        "sqc2 vf15, 0x10(%1)\n"
        "sqc2 vf16, 0x20(%1)\n"
        ".set reorder\n"
        : : "r"(*(Vec4 **)(chara + 0x13C)), "r"(m));
    m += 12;
    __asm__ __volatile__("sqc2 vf0, 0(%0)
" : : "r"(m) : "memory");
    D_00136B10.f[0] = x;
    D_00136B10.f[2] = z;
    __asm__ __volatile__(".set noreorder
"
                         "lqc2 vf8, 0(%2)
"
                         "lqc2 vf14, 0(%1)
"
                         "lqc2 vf15, 16(%1)
"
                         "lqc2 vf16, 32(%1)
"
                         "lqc2 vf17, 48(%1)
"
                         "vmulax.xyzw ACC, vf14, vf8x
"
                         "vmadday.xyzw ACC, vf15, vf8y
"
                         "vmaddaz.xyzw ACC, vf16, vf8z
"
                         "vmaddw.xyzw vf10, vf17, vf8w
"
                         "sqc2 vf10, 0(%0)
"
                         ".set reorder
"
                         : : "r"(out), "r"(matrix), "r"(&D_00136B10) : "memory");
}
