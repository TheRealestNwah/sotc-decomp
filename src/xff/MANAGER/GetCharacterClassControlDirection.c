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

void GetCharacterClassControlDirection(float *dst, char *c, float *v)
{
    __asm__ __volatile__("lqc2 vf08, 0x0(%2)\n"
                         "vaddw.xyz vf12, vf00, vf00w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         QUAT_ROWS
                         "vmulax.xyzw ACC, vf14, vf08x\n"
                         "vmadday.xyzw ACC, vf15, vf08y\n"
                         "vmaddaz.xyzw ACC, vf16, vf08z\n"
                         "vmaddw.xyzw vf10, vf00, vf08w\n"
                         "sqc2 vf10, 0x0(%0)\n.set noreorder\n.set reorder\n"
                         : : "r"(dst), "r"(*(void **)(c + 0x13C)), "r"(v) : "memory");
}
