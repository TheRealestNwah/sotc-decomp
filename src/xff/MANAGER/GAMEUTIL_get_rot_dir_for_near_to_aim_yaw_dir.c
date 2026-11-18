typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef union { s128 q[4]; float f[16]; } Matrix;

extern void iosRotMatrixY(float *, float);
extern void iosApplyRotMatrix(void *, void *, void *);

static inline int nearlyZero(float value, float tolerance)
{
    if (value < 0.0f) {
        if (-value <= tolerance)
            goto nearZero;
        else
            goto notNearZero;
    } else {
        if (value <= tolerance)
            goto nearZero;
        else
            goto notNearZero;
    }
nearZero:
    return 1;
notNearZero:
    return 0;
}

static inline int actYawRot(Vec4 *out, Vec4 *vector, float angle)
{
    Matrix matrix;

    if (nearlyZero(angle, 0.0001f) == 1) {
        out->q = vector->q;
        return 0;
    } else {
        iosRotMatrixY(matrix.f, angle);
        iosApplyRotMatrix(out, &matrix, vector);
        return 1;
    }
}

int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(Vec4 *out, Vec4 *cur, float speed, Vec4 *aim)
{
    Vec4 cross;
    float dot;
    int dir = 0;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(&cross), "r"(cur), "r"(aim) : "memory");
    if (cross.f[1] > 0.0f) {
        dir = 1;
    } else if (cross.f[1] < 0.0f) {
        dir = -1;
    } else {
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vaddw.x vf7, vf0, vf0w\n"
                             "vmul.xyz vf6, vf5, vf6\n"
                             "vaddax.x ACC, vf0, vf6x\n"
                             "vmadday.x ACC, vf7, vf6y\n"
                             "vmaddz.x vf6, vf7, vf6z\n"
                             "qmfc2.ni %0, vf6\n"
                             : "=r"(dot) : "r"(cur), "r"(aim));
        if (dot < 0.0f)
            dir = 1;
    }
    if (out != 0) {
        if (dir == 0)
            out->q = cur->q;
        else if (dir == 1)
            actYawRot(out, cur, speed);
        else
            actYawRot(out, cur, -speed);
    }
    return dir;
}
