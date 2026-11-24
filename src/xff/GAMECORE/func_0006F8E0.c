/* Sight-on base yaw driver: forces mode 1 when +0x14C is set, otherwise runs func_0006FC58, then (while +0x290 is set) picks the turn state through func_00070788/func_00070760/func_000708C0, either from is_predict_to_acting_base_yaw_rot_nico_yaw_pitch_cntrl (mode 1) or from the yaw gap to +0x150 (15 degree threshold when the motion is still, 10 degrees plus SCRPlayableCharaTurnDirectInput scaled by GAMEUTIL_get_dist_ratio otherwise), records +0x1A0, then resets the base yaw from the actor's local Z direction. Mode 2 sets the temporary stop flag before doit_nico_yaw_pitch_cntrl. In the yaw/pitch join block the actor load comes first (the Original copies it into the three branch delay slots) and the dir address is pinned to $4 ahead of the zero stores, held there by an empty asm. */
extern int is_predict_to_acting_base_yaw_rot_nico_yaw_pitch_cntrl(void *, float, float);
extern float get_base_yaw_nico_yaw_pitch_cntrl(void *);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern int GAMEUTIL_get_riding_horse_object(int);
extern char *GAMEUTIL_get_motion_kind(int);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern void SCRPlayableCharaTurnDirectInput(int, float);
extern void GAMEUTIL_get_local_directionZ(float *, int);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern void set_base_yaw_nico_yaw_pitch_cntrl(void *, float);
extern void set_temp_stop_base_rot_flag_nico_yaw_pitch_cntrl(void *, int);
extern void doit_nico_yaw_pitch_cntrl(void *, float, float);
extern void func_0006FC58(char *, float, float);
extern void func_00070760(void *);
extern void func_00070788(void *);
extern void func_000707B0(char *, int, int);
extern void func_000708C0(void *);

#define I(o) (*(int *)(w + (o)))
#define F(o) (*(float *)(w + (o)))

static void func_0006F8E0(char *w, float a, float b)
{
    float dir[4];
    float yaw;
    float pitch;
    char *c = w + 0xC;
    int prev;
    int s;
    float d;
    float r;
    int still;
    int h;
    char *m;

    if (I(0x14C) == 1) {
        I(0) = 1;
        goto stop;
    }
    prev = I(0);
    func_0006FC58(w, a, b);
    if (I(0x290) == 0) {
        if (I(0) == 2)
            func_000707B0(w, prev, 1);
    } else {
        s = I(0);
        if (s == 1) {
            if (is_predict_to_acting_base_yaw_rot_nico_yaw_pitch_cntrl(c, a, b) == s) {
                if (a > 0.0f)
                    func_00070788(w);
                else if (a < 0.0f)
                    func_00070760(w);
                else
                    func_000708C0(w);
            } else {
                func_000708C0(w);
            }
        } else {
            d = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(get_base_yaw_nico_yaw_pitch_cntrl(c), F(0x150));
            h = GAMEUTIL_get_riding_horse_object(I(4));
            if (h == 0)
                h = I(4);
            m = GAMEUTIL_get_motion_kind(h);
            if (m != 0 && *(int *)(m + 0x74) != 0)
                still = 0;
            else
                still = 1;
            if (prev != 2)
                I(0x1A0) = 0;
            if (still == 1) {
                float t = 0.26179937f;
                if (d < 0.0f ? -d > t : d > t) {
                    if (d > 0.0f)
                        func_00070788(w);
                    else
                        func_00070760(w);
                    I(0x1A0) = 1;
                } else {
                    func_000708C0(w);
                    I(0x1A0) = 0;
                }
            } else {
                r = GAMEUTIL_get_dist_ratio(d < 0.0f ? -d : d, 0.17453293f, 0.6981317f);
                if (d < 0.0f ? d < -0.17453293f : d > 0.17453293f) {
                    if (d > 0.0f) {
                        func_00070788(w);
                        SCRPlayableCharaTurnDirectInput(I(4), r);
                    } else {
                        func_00070760(w);
                        SCRPlayableCharaTurnDirectInput(I(4), -r);
                    }
                    I(0x1A0) = 1;
                } else {
                    func_000708C0(w);
                    SCRPlayableCharaTurnDirectInput(I(4), r);
                    I(0x1A0) = 0;
                }
            }
            func_000707B0(w, prev, 0);
        }
        { int o = I(4);
        register float *dp __asm__("$4") = dir;
        __asm__ __volatile__("" : : "r"(dp));
        yaw = 0.0f;
        pitch = 0.0f;
        GAMEUTIL_get_local_directionZ(dp, o); }
        GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, dir);
        set_base_yaw_nico_yaw_pitch_cntrl(c, yaw);
    }
    if (I(0) == 2) {
stop:
        set_temp_stop_base_rot_flag_nico_yaw_pitch_cntrl(c, 1);
    } else {
        set_temp_stop_base_rot_flag_nico_yaw_pitch_cntrl(c, 0);
    }
    doit_nico_yaw_pitch_cntrl(c, a, b);
}
