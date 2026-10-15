/* The empty noreorder block keeps the assembler from filling the return
   delay slot, as in the original. */
void iosTransposeRotationCurrentMatrix(void)
{
    __asm__ __volatile__(
                         "vsub.xyzw vf5, vf0, vf0\n"
                         "vaddx.y vf14, vf5, vf2x\n"
                         "vaddx.z vf14, vf5, vf3x\n"
                         "vaddy.x vf15, vf5, vf1y\n"
                         "vaddy.z vf15, vf5, vf3y\n"
                         "vaddz.x vf16, vf5, vf1z\n"
                         "vaddz.y vf16, vf5, vf2z\n"
                         "vmove.yz vf1, vf14\n"
                         "vmove.xz vf2, vf15\n"
                         "vmove.xy vf3, vf16\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : :  : "memory");
}
