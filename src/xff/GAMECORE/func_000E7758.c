extern float D_0017B720;
extern int CAM_is_visible_now_target_visibility(char *);
extern int is_safety_camera_default_angle(char *);
extern char *get_game_camera(char *);
extern int is_must_reach_normal_default_angle(char *, char *);
extern int CAM_motion_kind_is_accept_auto_rot_motion_target(char *);
extern int CAM_motion_kind_act_auto_yaw_rot_target(char *);
extern void CAM_interp_reset_aim_rot_common(char *);
extern void CAM_set_interp_param_extend_aim_rot_common(char *, float, float, float);
extern void CAM_set_interp_param_aim_rot_common(char *, float, float);
extern float CAM_doit_aim_angle_rot(char *, int, float, float, float, float, float, float, float, float, float);
extern float CAM_get_update_yaw_by_view_cut_avoid_cntrl(char *, char *, char *, float, float, float);
extern float CAM_get_update_pitch_by_view_cut_avoid_cntrl(char *, char *, char *, float, float, float);
extern int CAM_act_avoid_rot_obstacle_avoid_cntrl(char *, char *);
extern float act_pitch_rot_camera_target_approach(char *, float, float, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern float GAMEUTIL_get_difference_pitch_and_pitch(float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(char *, float, float);
extern void CAM_get_camera_position_by_look_at(char *, char *, char *, float);
extern void func_000ECDB0(void *, float *, int, float);
extern int func_000ECE28(float *, int, float *, float *, float);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define DEG 0.017453294f

static void func_000E7758(char *c, char *p, char *mgr)
{
    float keys[4];
    float vals[4];
    char *prm;
    char *look;
    char *ctl;
    float yawA;
    float pitchA;
    float yaw;
    float pitch;
    int force;
    int flag;
    int r1;
    int r2;
    int v;

    force = 0;
    look = c + 0xA0;
    prm = *(char **)p;
    yawA = F(c, 0xF30);
    pitchA = F(c, 0xF34);
    yaw = F(look, 0x30);
    pitch = F(look, 0x34);
    if (CAM_is_visible_now_target_visibility(c + 0x520) == 0 ||
        is_safety_camera_default_angle(c + 0x730) == 1 ||
        is_must_reach_normal_default_angle(c, get_game_camera(mgr)) == 0 ||
        I(*(char **)c, 4) == 2)
        force = 1;
    flag = 0;
    func_000ECDB0(keys, vals, 4, yaw);
    if (force == 1) {
        if (I(prm, 0x20) == 0) {
            v = I(prm, 0x24);
            if (v == 1 || (v == 2 && CAM_motion_kind_is_accept_auto_rot_motion_target(c + 0x23C) == 1))
                flag = 1;
        } else if (I(prm, 0x20) == 1) {
            flag = CAM_motion_kind_act_auto_yaw_rot_target(c + 0x23C) == force;
        }
    }
    if (flag == 1 && I(get_game_camera(mgr), 0x50) != 0 && 0.0f < F(prm, 0x28))
        CAM_interp_reset_aim_rot_common(p + 4);
    CAM_set_interp_param_extend_aim_rot_common(p + 4, F(prm, 0x28), F(prm, 0x2C), 0.29999998211860657f);
    vals[0] = CAM_doit_aim_angle_rot(p + 4, flag, yaw, yawA, F(prm, 0x30) * DEG, F(prm, 0x34) * DEG,
                                     F(prm, 0x38), F(prm, 0x3C), F(prm, 0x40), F(prm, 0x44), D_0017B720);
    vals[1] = CAM_get_update_yaw_by_view_cut_avoid_cntrl(c + 0x16B0, c, p, yaw, yawA, D_0017B720);
    flag = 0;
    keys[0] = GAMEUTIL_get_difference_yaw_and_yaw(yaw, vals[0]);
    keys[1] = GAMEUTIL_get_difference_yaw_and_yaw(yaw, vals[1]);
    r1 = func_000ECE28((float *)(look + 0x30), 4, keys, vals, yaw);
    func_000ECDB0(keys, vals, 4, pitch);
    if (force == 1) {
        v = I(prm, 0x48);
        if (v == 1 || (v == 2 && CAM_motion_kind_is_accept_auto_rot_motion_target(c + 0x23C) == 1))
            flag = 1;
    }
    if (flag == 1 && I(get_game_camera(mgr), 0x50) != 0 && 0.0f < F(prm, 0x4C))
        CAM_interp_reset_aim_rot_common(p + 0x48);
    CAM_set_interp_param_extend_aim_rot_common(p + 0x48, F(prm, 0x4C), F(prm, 0x50), 0.29999998211860657f);
    vals[0] = CAM_doit_aim_angle_rot(p + 0x48, flag, pitch, pitchA, F(prm, 0x54) * DEG, F(prm, 0x58) * DEG,
                                     F(prm, 0x5C), F(prm, 0x60), F(prm, 0x64), F(prm, 0x68), D_0017B720);
    vals[1] = CAM_get_update_pitch_by_view_cut_avoid_cntrl(c + 0x16B0, c, p, pitch, pitchA, D_0017B720);
    I(p, 0xD0) = CAM_act_avoid_rot_obstacle_avoid_cntrl(c, p);
    CAM_set_interp_param_aim_rot_common(p + 0x8C, 0.0f, 0.79999995231628418f);
    vals[2] = CAM_doit_aim_angle_rot(p + 0x8C, I(p, 0xD0), pitch, pitchA, F(prm, 0xB4) * DEG, F(prm, 0xB8) * DEG,
                                     F(prm, 0xBC), F(prm, 0xC0), F(prm, 0xC4), F(prm, 0xC8), D_0017B720);
    vals[3] = act_pitch_rot_camera_target_approach(c + 0x6A0, pitch, pitchA, D_0017B720);
    keys[0] = GAMEUTIL_get_difference_pitch_and_pitch(pitch, vals[0]);
    keys[1] = GAMEUTIL_get_difference_pitch_and_pitch(pitch, vals[1]);
    keys[2] = GAMEUTIL_get_difference_pitch_and_pitch(pitch, vals[2]);
    keys[3] = GAMEUTIL_get_difference_pitch_and_pitch(pitch, vals[3]);
    r2 = func_000ECE28((float *)(look + 0x34), 4, keys, vals, pitch);
    if (r1 == 1 || r2 == 1) {
        GAMEUTIL_get_direction_by_yaw_pitch(c + 0xC0, F(look, 0x30), F(look, 0x34));
        CAM_get_camera_position_by_look_at(look, c + 0xC0, c + 0xB0, F(look, 0x38));
        I(c, 0xF38) = r1;
        I(c, 0xF3C) = r2;
    }
}
