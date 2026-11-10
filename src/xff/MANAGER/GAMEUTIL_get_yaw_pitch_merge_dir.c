#ifdef NONMATCHING /* 2 diffs (volatile SetQuaternion declaration, found by the volatile sweep, cut it from 14): m[3] is derived from the laundered matrix pointer ($v1+0x30) instead of a fresh sp+0x50. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef float Mtx4[4][4] __attribute__((aligned(16)));
extern Vec4 YUnitVector;
extern float iosGetACosfExact(float);
extern volatile int SetQuaternionByAxisRotateVWithNoRegularize(Vec4 *, short, Vec4 *);
extern void iosApplyRotMatrix(Vec4 *, float (*)[4], Vec4 *);

static inline void outerProduct(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatToMatrix(float (*m)[4], Vec4 *q)
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
                         : : "r"(m), "r"(q) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(m[3]) : "memory");
}

void GAMEUTIL_get_yaw_pitch_merge_dir(Vec4 *out, Vec4 *dir, Vec4 *pitch_dir)
{
    Vec4 axis;
    Vec4 q;
    Mtx4 m;
    float ang;

    outerProduct(&axis, &YUnitVector, dir);
    ang = iosGetACosfExact(pitch_dir->f[2]);
    if (pitch_dir->f[1] < 0.0f) {
        ang = -ang;
    }
    if (1.48352981f < ang) {
        ang = 1.48352981f;
    } else if (ang < -1.48352981f) {
        ang = -1.48352981f;
    }
    SetQuaternionByAxisRotateVWithNoRegularize(&q, (short)(int)(ang * 32768.0f / 3.14159255f), &axis);
    { float (*mm)[4] = m; __asm__("" : "+r"(mm)); quatToMatrix(mm, &q); }
    iosApplyRotMatrix(out, m, dir);
}
#endif
