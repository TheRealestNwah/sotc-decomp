typedef int s128 __attribute__((mode(TI)));

extern s128 XUnitVector;
extern s128 YUnitVector;
extern s128 ZUnitVector;
extern void GetOffsetPositionAxis(s128 *, s128 *, float *, s128 *, s128 *, s128 *);

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

static inline int isZeroVector(float *v)
{
    float eps = 0.001f;

    if (ABS(v[0]) <= eps && ABS(v[1]) <= eps && ABS(v[2]) <= eps) {
        return 1;
    }
    return 0;
}

int GAMEUTIL_get_offset_position_by_option_space(s128 *out, s128 *base, float *offset, int space, s128 *ax, s128 *ay, s128 *az)
{
    s128 axes[3];

    if (!isZeroVector(offset)) {
        if (space == 1) {
            axes[0] = *ax;
            axes[1] = *ay;
            axes[2] = *az;
        } else {
            axes[0] = XUnitVector;
            axes[1] = YUnitVector;
            axes[2] = ZUnitVector;
        }
        GetOffsetPositionAxis(out, base, offset, &axes[0], &axes[1], &axes[2]);
        return 1;
    }
    *out = *base;
    return 0;
}
