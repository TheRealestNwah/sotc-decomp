/* Rotation-matrix rows of quaternion vf11 into vf14-vf16 (vf12 = 1). */
#define QUAT_ROWS \
    "vmr32.w vf14, vf00\n" \
    "vmr32.w vf15, vf00\n" \
    "vmr32.w vf16, vf00\n" \
    "vopmula.xyz ACC, vf11, vf12\n" \
    "vmadd.xyz vf11, vf00, vf00\n" \
    "vmadd.xyz vf10, vf11, vf12\n" \
    "vmul.xyz vf13, vf11, vf10\n" \
    "vopmula.xyz ACC, vf11, vf10\n" \
    "vmaddw.xyz vf15, vf10, vf11w\n" \
    "vmsubw.xyz vf16, vf10, vf11w\n" \
    "vopmula.xyz ACC, vf13, vf12\n" \
    "vmadd.xyz vf17, vf13, vf12\n" \
    "vopmula.xyz ACC, vf15, vf12\n" \
    "vmadd.xyz vf15, vf00, vf00\n" \
    "vsub.xyz vf14, vf12, vf17\n" \
    "vmove.yz vf17, vf14\n" \
    "vmove.y vf14, vf16\n" \
    "vmove.y vf16, vf15\n" \
    "vmove.y vf15, vf17\n" \
    "vmove.z vf14, vf15\n" \
    "vmove.z vf15, vf16\n" \
    "vmove.z vf16, vf17\n"

void GetMatrixFromQuatPos(float *dst, char *qp)
{
    char *pos = qp + 0x10;
    __asm__ __volatile__("vaddw.xyz vf12, vf00, vf00w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         QUAT_ROWS
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(dst), "r"(qp) : "memory");
    __asm__ __volatile__("lqc2 vf04, 0x0(%1)\n"
                         "vmove.w vf04, vf00\n"
                         "sqc2 vf04, 0x30(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dst), "r"(pos) : "memory");
}
