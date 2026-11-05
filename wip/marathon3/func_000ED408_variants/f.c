typedef int s128 __attribute__((mode(TI)));

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;
typedef struct { float m[4][4]; } __attribute__((aligned(16))) Mat;
extern s128 ZeroPoint;
extern s128 ZeroVector;
extern float YUnitVector[];
extern void GAMEUTIL_get_camera_target_look_at_position(void *, int);
extern void GAMEUTIL_get_vector_velocity_by_diff_move3D(void *, void *, void *, void *, float);
extern void iosRotMatrixAxis(float *, float, float *, int);
extern void iosApplyRotMatrix(float *, float *, float *);
extern void GAMEUTIL_get_divide_vector_value(float *, float *, float *, float *, float *, float *, float *);

static inline void vecCross(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vopmula.xyz ACC, vf05, vf06\n"
                         "vopmsub.xyz vf07, vf06, vf05\n"
                         "vsub.w vf07, vf07, vf07\n"
                         "sqc2 vf07, 0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf05, 0x0(%1)\n"
                         "vmul.xyz vf07, vf05, vf05\n"
                         "vmulax.w ACC, vf00, vf07x\n"
                         "vmadday.w ACC, vf00, vf07y\n"
                         "vmaddz.w vf07, vf00, vf07z\n"
                         "vrsqrt Q, vf00w, vf07w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf05, vf05, Q\n"
                         "sqc2 vf05, 0x0(%0)\n"
                         : : "r"(dst), "r"(src) : "memory");
}

void func_000DED78(s128 *out, char *cam, int mode, float time)
{
    s128 look[1];
    Vec4 x;
    Vec4 y;
    Mat m;
    Vec4 c;
    Vec4 d;
    s128 *vel = out + 2;
    float *axis = (float *)(cam + 0xC0);

    GAMEUTIL_get_camera_target_look_at_position(look, *(int *)(cam + 0x23C));
    if (mode == 1) {
        out[0] = ZeroPoint;
        out[1] = ZeroPoint;
        out[2] = ZeroVector;
        out[3] = ZeroVector;
        out[1] = look[0];
        ((int *)out)[17] = 0;
        ((int *)out)[16] = 0;
        out[0] = look[0];
        return;
    }
    out[0] = out[1];
    out[1] = look[0];
    GAMEUTIL_get_vector_velocity_by_diff_move3D(vel, vel, out, out + 1, time);
    iosRotMatrixAxis(m.m[0], *(float *)(cam + 0x1C0), axis, 1);
    vecCross(&c.x, YUnitVector, axis);
    vecNormalize(&c.x, &c.x);
    iosApplyRotMatrix(&x.x, m.m[0], &c.x);
    vecCross(&d.x, axis, &c.x);
    iosApplyRotMatrix(&y.x, m.m[0], &d.x);
    GAMEUTIL_get_divide_vector_value((float *)(out + 3), (float *)(out + 3) + 1, (float *)(out + 3) + 2,
                                     (float *)vel, &x.x, &y.x, axis);
}
