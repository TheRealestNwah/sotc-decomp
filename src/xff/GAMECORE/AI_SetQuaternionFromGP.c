typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern Vec4 *GetCollisionDBPlane(void *);
extern void GetGeometryPointerQuaternion(float *, void *);
extern void GetDifferencialQuaternionWithNoRegularize(float *, float *, void *, void *);
extern float iosGetRandom(void);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern void DivQuaternion(float *, float *, float *);
extern char XUnitVector[], YUnitVector[];

#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory")

void AI_SetQuaternionFromGP(float *q, void *gp)
{
    Vec4 plane;
    Vec4 gq;
    Vec4 rq;

    plane.q = GetCollisionDBPlane(gp)->q;
    plane.f[3] = 1.0f;
    GetGeometryPointerQuaternion(gq.f, gp);
    GetDifferencialQuaternionWithNoRegularize(q, plane.f, YUnitVector, XUnitVector);
    SetQuaternionByAxisRotateVWithNoRegularize(rq.f,
        (int)(iosGetRandom() * 6.2831850051879883f * 32768.0f / 3.14159262f), YUnitVector);
    VU_QUAT_MUL(q, q, rq.f);
    DivQuaternion(q, q, gq.f);
}
