void CAM_get_camera_position_by_look_at(float *pos, float *dir, float *look_at, float dist)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(t), "r"(dir), "r"(-dist) : "memory");
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vadd.xyz vf05, vf05, vf06\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(pos), "r"(look_at), "r"(t) : "memory");
}
