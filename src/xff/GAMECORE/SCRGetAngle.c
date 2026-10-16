extern void iosGetStabXZVector(float *, float *);
extern float iosGetACosfExact(float);

float SCRGetAngle(float *from, float *dir, float *to)
{
    float v[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float dot;
    float a;
    float r;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(v), "r"(to), "r"(from) : "memory");
    iosGetStabXZVector(v, v);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(v), "r"(dir) : "$2");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(c), "r"(v), "r"(dir) : "memory");
    a = iosGetACosfExact(dot);
    r = -a;
    if (c[1] < 0.0f)
        r = a;
    return r;
}
