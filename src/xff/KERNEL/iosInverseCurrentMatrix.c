void iosInverseCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vsub.xyzw vf5, vf0, vf0\n"
        "vsubw.x vf6, vf0, vf0w\n"
        "vaddx.y vf14, vf5, vf2x\n"
        "vaddx.z vf14, vf5, vf3x\n"
        "vaddy.x vf15, vf5, vf1y\n"
        "vaddy.z vf15, vf5, vf3y\n"
        "vaddz.x vf16, vf5, vf1z\n"
        "vaddz.y vf16, vf5, vf2z\n"
        "vmulx.xyz vf17, vf4, vf6x\n"
        "vmove.yz vf1, vf14\n"
        "vmove.xz vf2, vf15\n"
        "vmove.xy vf3, vf16\n"
        "vmove.w vf17, vf0\n"
        "vmulax.xyzw ACC, vf1, vf17x\n"
        "vmadday.xyzw ACC, vf2, vf17y\n"
        "vmaddaz.xyzw ACC, vf3, vf17z\n"
        "vmaddw.xyzw vf4, vf0, vf17w\n"
        ".set reorder\n"
        : : : "memory");
}
