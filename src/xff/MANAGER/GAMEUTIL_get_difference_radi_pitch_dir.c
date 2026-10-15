extern float iosGetACosfExact(float);

float GAMEUTIL_get_difference_radi_pitch_dir(float *a, float *b)
{
    float d;
    float r;
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vaddw.x vf07, vf00, vf00w\n"
                         "vmul.xyz vf06, vf05, vf06\n"
                         "vaddax.x ACC, vf00, vf06x\n"
                         "vmadday.x ACC, vf07, vf06y\n"
                         "vmaddz.x vf06, vf07, vf06z\n"
                         "qmfc2 %0, vf06\n"
                         : "=r"(d) : "r"(a), "r"(b));
    r = iosGetACosfExact(d);
    a = 0;
    return r;
}
