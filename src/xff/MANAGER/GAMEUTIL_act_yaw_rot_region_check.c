/* Rotates in by angle (or copies it when angle is ~0), then clips the result against the yaw region [v10,v20]. The rotation goes through an inline helper taking the matrix by pointer, so gcc recomputes its stack address per call; pv keeps &v0 in $s0 like the Original. */
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

static inline void rotApplyM(Matrix *mm, Vec4 *out, float a, Vec4 *in)
{
    iosRotMatrixY(mm->f, a);
    iosApplyRotMatrix(out, mm, in);
}

int GAMEUTIL_act_yaw_rot_region_check(Vec4 *out, Vec4 *in, int a2, int a3, float angle, float limit)
{
    Vec4 v0;
    Vec4 *pv = &v0;
    Vec4 v10;
    Vec4 v20;
    Matrix m;
    int r;

    v0.q = in->q;
    if (nearlyZero(angle, 0.0001f) == 1) {
        out->q = pv->q;
        r = 0;
    } else {
        rotApplyM(&m, out, angle, pv);
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
