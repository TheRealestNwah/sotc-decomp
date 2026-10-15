typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void SetQuaternionByAxisRotate(Vec4 *, short, float, float, float);
extern void func_000078C8(void *, Vec4 *);

void GAMEUTIL_act_axis_rot_root_quaternion_abs(void *q, float *axis, float ang)
{
    Vec4 r;
    SetQuaternionByAxisRotate(&r, -(int)(ang * 32768.0f / 3.1415926f), axis[0], axis[1], axis[2]);
    func_000078C8(q, &r);
}
