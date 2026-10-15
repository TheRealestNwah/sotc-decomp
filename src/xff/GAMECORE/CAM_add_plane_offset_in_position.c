void CAM_add_plane_offset_in_position(float *out, float *pos, float *dir, float scale)
{
    float tmp[4] __attribute__((aligned(16)));

    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0x0(%0)\n"
                         : : "r"(tmp), "r"(dir), "r"(scale) : "memory");
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "lqc2 vf06, 0x0(%2)\n"
                         "vadd.xyz vf05, vf05, vf06\n"
                         "sqc2 vf05, 0x0(%0)\n"
                         : : "r"(out), "r"(pos), "r"(tmp) : "memory");
}
