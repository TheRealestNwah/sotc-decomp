extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);

void update_by_cam_and_look_at_posi_mode_common_camera_data(char *data)
{
    float *dir = (float *)(data + 0x20);
    float len;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dir), "r"(data + 0x10), "r"(data) : "memory");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(dir) : "$2");
    *(float *)(data + 0x38) = len;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2 %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dir), "r"(1.0f / len) : "memory");
    GAMEUTIL_get_yaw_pitch_by_direction((float *)(data + 0x30), (float *)(data + 0x34), dir);
}
