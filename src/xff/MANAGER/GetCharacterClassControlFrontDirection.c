void GetCharacterClassControlFrontDirection(float *dir, char *c)
{
    __asm__ __volatile__("lqc2 vf04, 0(%1)\n"
                         "vmul.xyzw vf05, vf04, vf04\n"
                         "vmr32.xyzw vf06, vf04\n"
                         "vmul.xyzw vf07, vf06, vf04\n"
                         "vmr32.xyzw vf06, vf06\n"
                         "vmul.xyzw vf08, vf06, vf04\n"
                         "vsubx.z vf06, vf00, vf05x\n"
                         "vsuby.z vf06, vf06, vf05y\n"
                         "vaddw.y vf06, vf07, vf07w\n"
                         "vsuby.x vf06, vf08, vf08y\n"
                         "vsub.w vf06, vf00, vf00\n"
                         "vadd.w vf05, vf00, vf00\n"
                         "vmulw.xyz vf06, vf06, vf05w\n"
                         "vaddw.z vf06, vf06, vf00w\n"
                         "sqc2 vf06, 0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(dir), "r"(c + 0x470) : "memory");
}
