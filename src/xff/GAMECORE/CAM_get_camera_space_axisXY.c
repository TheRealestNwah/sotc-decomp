typedef float Vec4[4] __attribute__((aligned(16)));

extern Vec4 YUnitVector;
extern void iosRotMatrixAxis(float *, float, float *, int);
extern void iosApplyRotMatrix(float *, float *, float *);

static inline void vecCross(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(float *output, float *input)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(output), "r"(input) : "memory");
}

int CAM_get_camera_space_axisXY(float *x, float *y, float *dir, float rot)
{
    Vec4 m[4];
    Vec4 side;
    Vec4 up;

    iosRotMatrixAxis(m[0], rot, dir, 1);
    vecCross(side, YUnitVector, dir);
    vecNormalize(side, side);
    if (x != 0)
        iosApplyRotMatrix(x, m[0], side);
    if (y != 0) {
        vecCross(up, dir, side);
        iosApplyRotMatrix(y, m[0], up);
    }
    if (dir[1] < 0.0f ? -0.9999f <= dir[1] : dir[1] <= 0.9999f)
        return 1;
    return 0;
}
