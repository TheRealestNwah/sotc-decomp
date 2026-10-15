void iosInverseCurrentMatrix(void)
{
    __asm__ __volatile__("vsub.xyzw vf05, vf00, vf00\n"
                         "vsubw.x vf06, vf00, vf00w\n"
                         "vaddx.y vf14, vf05, vf02x\n"
                         "vaddx.z vf14, vf05, vf03x\n"
                         "vaddy.x vf15, vf05, vf01y\n"
                         "vaddy.z vf15, vf05, vf03y\n"
                         "vaddz.x vf16, vf05, vf01z\n"
                         "vaddz.y vf16, vf05, vf02z\n"
                         "vmulx.xyz vf17, vf04, vf06x\n"
                         "vmove.yz vf01, vf14\n"
                         "vmove.xz vf02, vf15\n"
                         "vmove.xy vf03, vf16\n"
                         "vmove.w vf17, vf00\n"
                         "vmulax.xyzw ACC, vf01, vf17x\n"
                         "vmadday.xyzw ACC, vf02, vf17y\n"
                         "vmaddaz.xyzw ACC, vf03, vf17z\n"
                         "vmaddw.xyzw vf04, vf00, vf17w\n"
                         ".set noreorder\n"
                         ".set reorder\n");
}
