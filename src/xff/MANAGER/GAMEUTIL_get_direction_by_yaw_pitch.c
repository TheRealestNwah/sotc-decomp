#ifdef NONMATCHING /* stack layout matches; gcc keeps the matrix/quat address in s0 instead of rot (33 diffs) */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern void iosRotMatrixY(void *, float);
extern void iosApplyRotMatrix(void *, void *, void *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern char ZUnitVector[], YUnitVector[];

static inline void crossXYZ(float *out, const void *a, const void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatToMatrix(Vec4 *m, float *quat)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(m), "r"(quat) : "memory");
    m += 3;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(m) : "memory");
}

void GAMEUTIL_get_direction_by_yaw_pitch(Vec4 *out, float yaw, float pitch)
{
    Vec4 rot[4];
    float m[16] __attribute__((aligned(16)));
    Vec4 axis;
    Vec4 quat;

    iosRotMatrixY(m, yaw);
    iosApplyRotMatrix(out, m, ZUnitVector);
    crossXYZ(axis.f, YUnitVector, out);
    SetQuaternionByAxisRotateVWithNoRegularize(quat.f, (int)(pitch * 32768.0f / 3.14159262f), axis.f);
    quatToMatrix(rot, quat.f);
    iosApplyRotMatrix(out, rot, out);
}
#endif
