extern void iosGetSinCosf(float *, float);

void iosRotCurrentMatrixX(float angle)
{
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(".set noreorder\n"
                         "vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         ".set reorder\n");
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "mfc1 $9, %1\n"
                         "qmtc2.ni $8, vf5\n"
                         "qmtc2.ni $9, vf6\n"
                         "vaddx.y vf15, vf0, vf5x\n"
                         "vsubx.y vf16, vf0, vf6x\n"
                         "vaddx.z vf15, vf0, vf6x\n"
                         "vaddx.z vf16, vf0, vf5x\n"
                         "vmulax.xyzw ACC, vf1, vf14x\n"
                         "vmadday.xyzw ACC, vf2, vf14y\n"
                         "vmaddaz.xyzw ACC, vf3, vf14z\n"
                         "vmaddw.xyzw vf14, vf4, vf14w\n"
                         "vmulax.xyzw ACC, vf1, vf15x\n"
                         "vmadday.xyzw ACC, vf2, vf15y\n"
                         "vmaddaz.xyzw ACC, vf3, vf15z\n"
                         "vmaddw.xyzw vf15, vf4, vf15w\n"
                         "vmulax.xyzw ACC, vf1, vf16x\n"
                         "vmadday.xyzw ACC, vf2, vf16y\n"
                         "vmaddaz.xyzw ACC, vf3, vf16z\n"
                         "vmaddw.xyzw vf16, vf4, vf16w\n"
                         "vmulax.xyzw ACC, vf1, vf17x\n"
                         "vmadday.xyzw ACC, vf2, vf17y\n"
                         "vmaddaz.xyzw ACC, vf3, vf17z\n"
                         "vmaddw.xyzw vf17, vf4, vf17w\n"
                         "vmove.xyzw vf1, vf14\n"
                         "vmove.xyzw vf2, vf15\n"
                         "vmove.xyzw vf3, vf16\n"
                         "vmove.xyzw vf4, vf17\n"
                         ".set reorder\n"
                         : : "f"(sc[0]), "f"(sc[1]) : "$8", "$9");
}
