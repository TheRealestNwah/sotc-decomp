extern int is_doing_nico_sight_on(void *);
extern float get_base_yaw_nico_yaw_pitch_cntrl(void *);
extern float get_base_yaw_move_nico_yaw_pitch_cntrl(void *);
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern void GAMEUTIL_get_local_directionZ(float *, int);
extern int GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern void func_0006F8E0(void *, float, float);
extern void func_0006ED88(void *, float, int);
extern void func_0006F230(void *, float, float, int);
extern void func_00070788(void *);
extern void func_00070760(void *);
extern void func_00070710(void *, float);

void doit_nico_sight_on(char *o, float f0, float f1, float f2)
{
    int on = is_doing_nico_sight_on(o);

    if (on != 1)
        return;
    func_0006F8E0(o, f1, f2);
    func_0006ED88(o, f0, 0);
    func_0006F230(o, f1, f2, 0);
    *(int *)(o + 0x14C) = 0;
    if (*(int *)(o + 0x294) == 2) {
        char *q = o + 0xC;
        int ok = 0;

        if (*(int *)o == on) {
            if (!GAMEUTIL_is_nearly_equal_zero(get_base_yaw_move_nico_yaw_pitch_cntrl(q), 0.0003f))
                ok = 1;
        } else {
            if (GAMEUTIL_get_difference_yaw_and_yaw(get_base_yaw_nico_yaw_pitch_cntrl(q), *(float *)(o + 0x150)) >= 0.17453293f)
                ok = 1;
        }
        if (ok == 1) {
            float r = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(*(float *)(o + 0x280), *(float *)(o + 0x270));

            if (!GAMEUTIL_is_nearly_equal_zero(r, 0.0003f)) {
                if (r > 0.0f)
                    func_00070788(o);
                else
                    func_00070760(o);
            }
        }
        func_00070710(o, *(float *)(o + 0x280));
    } else if (*(int *)(o + 0x294) == on) {
        on = *(int *)(o + 0x2B8);

        if (on == *(int *)(o + 0x294)) {
            float dir[4];
            float yp[2];
            float zero = 0.0f;

            yp[0] = zero;
            yp[1] = zero;
            GAMEUTIL_get_local_directionZ(dir, *(int *)(o + 4));
            GAMEUTIL_get_yaw_pitch_by_direction(&yp[0], &yp[1], dir);
            if (GAMEUTIL_get_difference_yaw_and_yaw(GAMEUTIL_increase_yaw(0, yp[0], *(float *)(o + 0x2C4)), *(float *)(o + 0x200)) >= 2.268927812576294f)
                *(int *)(o + 0x14C) = on;
        }
    }
}
