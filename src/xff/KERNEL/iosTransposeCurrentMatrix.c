void iosTransposeCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vsub.xyzw vf5, vf0, vf0\n"
        "vaddx.y vf14, vf5, vf2x\n"
        "vaddx.z vf14, vf5, vf3x\n"
        "vaddx.w vf14, vf5, vf4x\n"
        "vaddy.x vf15, vf5, vf1y\n"
        "vaddy.z vf15, vf5, vf3y\n"
        "vaddy.w vf15, vf5, vf4y\n"
        "vaddz.x vf16, vf5, vf1z\n"
        "vaddz.y vf16, vf5, vf2z\n"
        "vaddz.w vf16, vf5, vf4z\n"
        "vaddw.x vf17, vf5, vf1w\n"
        "vaddw.y vf17, vf5, vf2w\n"
        "vaddw.z vf17, vf5, vf3w\n"
        "vmove.yzw vf1, vf14\n"
        "vmove.xzw vf2, vf15\n"
        "vmove.xyw vf3, vf16\n"
        "vmove.xyz vf4, vf17\n"
        ".set reorder\n"
        : : : "memory");
}
