/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosScaleCurrentMatrix(float x, float y, float z)
{
    __asm__ __volatile__("vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         "mfc1 $6, %0\n"
                         "mfc1 $7, %1\n"
                         "mfc1 $8, %2\n"
                         "qmtc2 $6, vf5\n"
                         "qmtc2 $7, vf6\n"
                         "qmtc2 $8, vf7\n"
                         "vaddx.x vf14, vf0, vf5x\n"
                         "vaddx.y vf15, vf0, vf6x\n"
                         "vaddx.z vf16, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf1, vf14x
"
                         "vmadday.xyzw ACC, vf2, vf14y
"
                         "vmaddaz.xyzw ACC, vf3, vf14z
"
                         "vmaddw.xyzw vf14, vf4, vf14w
"
                         "vmulax.xyzw ACC, vf1, vf15x
"
                         "vmadday.xyzw ACC, vf2, vf15y
"
                         "vmaddaz.xyzw ACC, vf3, vf15z
"
                         "vmaddw.xyzw vf15, vf4, vf15w
"
                         "vmulax.xyzw ACC, vf1, vf16x
"
                         "vmadday.xyzw ACC, vf2, vf16y
"
                         "vmaddaz.xyzw ACC, vf3, vf16z
"
                         "vmaddw.xyzw vf16, vf4, vf16w
"
                         "vmulax.xyzw ACC, vf1, vf17x
"
                         "vmadday.xyzw ACC, vf2, vf17y
"
                         "vmaddaz.xyzw ACC, vf3, vf17z
"
                         "vmaddw.xyzw vf17, vf4, vf17w
"
                         "vmove.xyzw vf1, vf14\n"
                         "vmove.xyzw vf2, vf15\n"
                         "vmove.xyzw vf3, vf16\n"
                         "vmove.xyzw vf4, vf17\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "f"(x), "f"(y), "f"(z) : "$6", "$7", "$8");
}
