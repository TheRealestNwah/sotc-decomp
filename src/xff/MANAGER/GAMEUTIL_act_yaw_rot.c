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

int GAMEUTIL_act_yaw_rot(Vec4 *out, Vec4 *vector, float angle)
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
