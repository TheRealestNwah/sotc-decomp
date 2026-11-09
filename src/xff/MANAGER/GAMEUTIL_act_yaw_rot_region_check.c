#ifdef NONMATCHING
/* 121 diffs, 2 words longer (136 vs 134). Draft from GAMEUTIL_act_yaw_rot (rot-matrix idiom) plus the matched is_yaw_dir_sandwich / get_difference_radi_yaw_dir; callee protos for is_yaw_dir_inside_of_region and get_rot_dir_for_near_to_aim_yaw_dir are guesses from their call sites. Semantics: rotate 'in' by angle (or copy if ~0), then if rotated, clip the result against the yaw region [v10,v20] (inside + sandwich checks, else pick the nearer edge v30 and cancel the rotation when it points the wrong way). The Original keeps &v0 (sp+0) cached in $s0 and shares sp+0x30 between the Matrix and v30; ours caches the matrix address. Frame size matches (0xC0). Permuter (12 workers, 25 min): 1130 -> 940 only. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef union { s128 q[4]; float f[16]; } Matrix;

extern void iosRotMatrixY(float *, float);
extern void iosApplyRotMatrix(void *, void *, void *);
extern int GAMEUTIL_is_yaw_dir_inside_of_region(Vec4 *, Vec4 *, Vec4 *, int, float);
extern int GAMEUTIL_is_yaw_dir_sandwich(Vec4 *, Vec4 *, Vec4 *);
extern float GAMEUTIL_get_difference_radi_yaw_dir(Vec4 *, Vec4 *);
extern int GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(void *, Vec4 *, float, Vec4 *);

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

int GAMEUTIL_act_yaw_rot_region_check(Vec4 *out, Vec4 *in, int a2, int a3, float angle, float limit)
{
    Vec4 v0;
    Vec4 v10;
    Vec4 v20;
    Matrix m;
    int r;

    v0.q = in->q;
    if (nearlyZero(angle, 0.0001f) == 1) {
        out->q = v0.q;
        r = 0;
    } else {
        iosRotMatrixY(m.f, angle);
        iosApplyRotMatrix(out, &m, &v0);
        r = 1;
    }
    if (r == 1) {
        if (GAMEUTIL_is_yaw_dir_inside_of_region(&v10, &v20, &v0, a2, limit) == r) {
            if (GAMEUTIL_is_yaw_dir_sandwich(&v10, &v0, out) == r) {
                out->q = v10.q;
            } else if (GAMEUTIL_is_yaw_dir_sandwich(&v20, &v0, out) == r) {
                out->q = v20.q;
            }
        } else {
            float d1 = GAMEUTIL_get_difference_radi_yaw_dir(&v0, &v10);
            float d2 = GAMEUTIL_get_difference_radi_yaw_dir(&v0, &v20);
            float zero;
            int rd;

            if (d1 < d2)
                m.q[0] = v10.q;
            else
                m.q[0] = v20.q;
            zero = 0.0f;
            rd = GAMEUTIL_get_rot_dir_for_near_to_aim_yaw_dir(0, &v0, zero, (Vec4 *)&m);
            if ((rd == 1 && angle < zero) || (rd == -1 && zero < angle)) {
                r = 0;
                out->q = v0.q;
            } else if (a3 != 0) {
                if (GAMEUTIL_is_yaw_dir_sandwich((Vec4 *)&m, &v0, out) == 1)
                    out->q = m.q[0];
            }
        }
    }
    return r;
}
#endif
