typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern void GetPlaneZTopYPlaneCoordQuaternion(Vec4 *, void *);
extern float GetTurnYAngleFromGlobalDir(Vec4 *, Vec4 *);

float charrootdyn_getCharaFront_PlaneTopDifferenceXZAngle(Vec4 *q, void *x)
{
    Vec4 plane, dir;
    GetPlaneZTopYPlaneCoordQuaternion(&plane, x);
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
                         : : "r"(&dir), "r"(q) : "memory");
    return GetTurnYAngleFromGlobalDir(&plane, &dir);
}
