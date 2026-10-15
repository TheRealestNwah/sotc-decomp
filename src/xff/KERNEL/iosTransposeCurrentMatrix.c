void iosTransposeCurrentMatrix(void)
{
    __asm__ __volatile__("vsub.xyzw vf05, vf00, vf00\n"
                         "vaddx.y vf14, vf05, vf02x\n"
                         "vaddx.z vf14, vf05, vf03x\n"
                         "vaddx.w vf14, vf05, vf04x\n"
                         "vaddy.x vf15, vf05, vf01y\n"
                         "vaddy.z vf15, vf05, vf03y\n"
                         "vaddy.w vf15, vf05, vf04y\n"
                         "vaddz.x vf16, vf05, vf01z\n"
                         "vaddz.y vf16, vf05, vf02z\n"
                         "vaddz.w vf16, vf05, vf04z\n"
                         "vaddw.x vf17, vf05, vf01w\n"
                         "vaddw.y vf17, vf05, vf02w\n"
                         "vaddw.z vf17, vf05, vf03w\n"
                         "vmove.yzw vf01, vf14\n"
                         "vmove.xzw vf02, vf15\n"
                         "vmove.xyw vf03, vf16\n"
                         "vmove.xyz vf04, vf17\n"
                         ".set noreorder\n"
                         ".set reorder\n");
}
