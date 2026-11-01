extern float iosGetATan2fExact(float, float);
extern float YUnitVector[];
extern float IdentityQuaternion[];
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *q, short angle, float *axis);

float GetYRotLimitQuaternionFromDir(float *out, float *dir, float limit)
{
    float r[4] __attribute__((aligned(16)));
    float *id;
    short ang;
    float a = iosGetATan2fExact(dir[0], dir[2]);

    id = IdentityQuaternion;
    if (a < 0.0f ? limit < -a : limit < a) {
        a = a < 0.0f ? -limit : limit;
    }
    ang = a * 32768.0f / 3.1415925026f;
    SetQuaternionByAxisRotateVWithNoRegularize(r, -ang, YUnitVector);
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(id), "r"(r), "r"(out) : "memory");
    return a;
}
