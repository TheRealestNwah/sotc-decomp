typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vector;
extern int GetMotionRootDirInfo(float *, void *, float);
extern float GetQuaternionAxisRotInfo(s128 *, float *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);
extern void MultiGlobalQuaternionToRootSkeleton(void *, void *, void *);

int GetScalableTurnQuaternionArray(float *out, void *quaternions, void *motion,
                                   void *skeleton, float frame, float scale)
{
    Vector rotation, axis;
    if (GetMotionRootDirInfo(out, motion, frame)) {
        if (scale != 1.0f) {
            float angle = GetQuaternionAxisRotInfo(&axis.q, out);
            SetQuaternionByAxisRotateVWithNoRegularize(rotation.f,
                (int)(angle * (scale - 1.0f) * 32768.0f / 3.1415926f), axis.f);
            MultiGlobalQuaternionToRootSkeleton(quaternions, &rotation, skeleton);
            __asm__ __volatile__("lqc2 vf11, 0(%1)\n"
                                 "lqc2 vf12, 0(%2)\n"
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
                                 "sqc2 vf13, 0(%0)\n"
                                 : : "r"(out), "r"(out), "r"(&rotation) : "memory");
        }
        return 1;
    } else {
        __asm__ __volatile__("sqc2 vf0, 0(%0)\n" : : "r"(out) : "memory");
        return 0;
    }
}
