void set_camera_up_direction(char *cam, float *v)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "vmul.xyz vf07, vf05, vf05\n"
                         "vmulax.w ACC, vf00, vf07x\n"
                         "vmadday.w ACC, vf00, vf07y\n"
                         "vmaddz.w vf07, vf00, vf07z\n"
                         "vrsqrt Q, vf00w, vf07w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf05, vf05, Q\n"
                         "sqc2 vf05, 0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(cam + 0x200), "r"(v) : "memory");
}
