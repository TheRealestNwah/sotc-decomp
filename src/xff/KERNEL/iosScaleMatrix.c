void iosScaleMatrix(float *m, float x, float y, float z)
{
    __asm__ __volatile__("vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         "sqc2 vf17, 0x30(%0)\n"
                         : : "r"(m) : "memory");
    m[0] = x;
    m[5] = y;
    m[10] = z;
}
