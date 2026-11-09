#ifdef NONMATCHING
/* 5 diffs, same length (129 words). Draft from GAMEUTIL_act_yaw_rot (nearlyZero/rot-matrix idiom) and the pitch limits in GAMEUTIL_increase_pitch_limit_clip. Signature (out, cur, axis, speed, lo, hi): act_pitch_rot, then clamp the resulting pitch to +-85 deg and, if it is past lo or hi, re-aim out at that (clamped) limit. Remaining diffs: gcc caches the Matrix address in $s0 across the calls where the Original recomputes sp each time (empty-asm +r tricks and a shared-matrix/goto structure were worse: 6 and 48). The 'float zero' local is what moves the 0.0f into $f20. Permuter (12 workers, 25 min): no improvement. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef union { s128 q[4]; float f[16]; } Matrix;

extern Vec4 ZUnitVector;
extern int GAMEUTIL_act_pitch_rot(Vec4 *, Vec4 *, int, float, float, float);
extern float iosGetACosfExact(float);
extern void iosRotMatrixX(float *, float);
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

static inline void applyLimit(Vec4 *out, Matrix *mp, float limit)
{
#define matrix (*mp)

    if (nearlyZero(limit, 0.0001f) == 1) {
        out->q = ZUnitVector.q;
    } else {
        if (1.4835299f < limit)
            limit = 1.4835299f;
        else if (limit < -1.4835299f)
            limit = -1.4835299f;
        iosRotMatrixX(matrix.f, -limit);
        iosApplyRotMatrix(out, &matrix, &ZUnitVector);
    }
#undef matrix
}

int GAMEUTIL_act_pitch_rot_limit_clip(Vec4 *out, Vec4 *cur, int axis, float speed, float lo, float hi)
{
    Matrix m;
    int r = GAMEUTIL_act_pitch_rot(out, cur, axis, speed, lo, hi);
    float zero = 0.0f;
    float p = iosGetACosfExact(out->f[2]);

    if (out->f[1] < zero)
        p = -p;
    if (1.4835299f < p)
        p = 1.4835299f;
    else if (p < -1.4835299f)
        p = -1.4835299f;
    if (lo < p) {
        applyLimit(out, &m, lo);
        r = 1;
    } else if (p < hi) {
        applyLimit(out, &m, hi);
        r = 1;
    }
    return r;
}
#endif
