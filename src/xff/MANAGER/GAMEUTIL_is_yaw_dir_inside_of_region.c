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


#define OUTER(dst, a, b) \
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n" \
                         "lqc2 vf6, 0x0(%2)\n" \
                         "vopmula.xyz ACC, vf5, vf6\n" \
                         "vopmsub.xyz vf7, vf6, vf5\n" \
                         "vsub.w vf7, vf7, vf7\n" \
                         "sqc2 vf7, 0x0(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

int GAMEUTIL_is_yaw_dir_inside_of_region(Vec4 *left, Vec4 *right, Vec4 *dir, Vec4 *center, float range)
{
    Vec4 l;
    Vec4 r;
    float half = range * 0.5f;

    actYawRot(&l, center, half);
    actYawRot(&r, center, -half);
    if (left != 0)
        left->q = l.q;
    if (right != 0)
        right->q = r.q;
    {
    Vec4 c1;
    Vec4 c2;
    Vec4 c3;
    Vec4 *lp = &l;
    Vec4 *rp = &r;
    OUTER(&c1, lp, dir);
    OUTER(&c2, lp, rp);
    if (c1.f[1] * c2.f[1] > 0.0f) {
        OUTER(&c3, dir, rp);
        return c2.f[1] * c3.f[1] > 0.0f;
    }
    }
    return 0;
}
