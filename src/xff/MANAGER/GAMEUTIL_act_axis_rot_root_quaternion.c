typedef int s128 __attribute__((mode(TI)));

extern char *GetLayoutClass(void *);
extern void SetQuaternionByAxisRotate(s128 *, short, float, float, float);
extern void func_000078C8(void *, s128 *);

void GAMEUTIL_act_axis_rot_root_quaternion(void *obj, float *axis, float angle)
{
    s128 v[2];
    char *cls = GetLayoutClass(obj);

    SetQuaternionByAxisRotate(&v[0], -(int)(angle * 32768.0f / 3.14159262f), axis[0], axis[1], axis[2]);
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
                         : : "r"(*(s128 **)(cls + 0x13C)), "r"(&v[0]), "r"(&v[1]) : "memory");
    func_000078C8(obj, &v[1]);
}
