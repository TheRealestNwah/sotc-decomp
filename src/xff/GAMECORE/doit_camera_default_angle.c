extern int is_reset_or_lws_movie_or_cutout_game_camera(void *);
extern void CAM_reset_slope_cntrl(void *);
extern void CAM_doit_slope_cntrl(void *, void *, void *, float);
extern void func_000D6410(void *, void *, void *, void *, int, float);
extern void GAMEUTIL_set_act_interp_flag_interp_ratio_cntrl(void *, int);
extern void reset_aim_angle_interp_cntrl(void *, float);
extern int is_base_default_dir_attr_change_game_camera_param_manager(void *);
extern void GAMEUTIL_reset_interp_ratio_cntrl(void *);
extern float get_interp_time_game_camera_param_manager(void *);
extern void GAMEUTIL_set_param_interp_ratio_cntrl(void *, float, float);
extern void set_interp_param_aim_angle_interp_cntrl(void *, float, float);
extern int GAMEUTIL_get_cur_status_status_manager(void *);
extern int GAMEUTIL_is_status_change_status_manager(void *);
extern void doit_aim_angle_interp_cntrl(void *, float, float, int, float);
extern int is_cut_default_pitch_interp_camera_target_approach(void *);
extern void GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(void *);
extern float GAMEUTIL_doit_interp_ratio_cntrl(void *, float);
extern void func_000D6C88(void *, void *);

void doit_camera_default_angle(char *cn, char *cam, char *a2, char *a3, float dt)
{
    int reset = is_reset_or_lws_movie_or_cutout_game_camera(a2);
    char *p;
    char *q;
    char *s7;
    char *aim1;
    char *aim2;
    int s6;
    int fp;

    if (reset == 1)
        CAM_reset_slope_cntrl(cn + 0x90);
    else
        CAM_doit_slope_cntrl(cn + 0x90, cam, a3, dt);
    func_000D6410(cn, cam, a2, a3, reset, dt);
    if (reset == 1) {
        GAMEUTIL_set_act_interp_flag_interp_ratio_cntrl(cn + 0x60, 0);
        reset_aim_angle_interp_cntrl(cn + 0x10, *(float *)(cn + 0x30));
        reset_aim_angle_interp_cntrl(cn + 0x20, *(float *)(cn + 0x34));
    } else {
        p = cn + 0x60;
        q = a2 + 0x50;
        GAMEUTIL_set_act_interp_flag_interp_ratio_cntrl(p, 1);
        s7 = cam + 0xA0;
        fp = 0;
        s6 = 0;
        if (is_base_default_dir_attr_change_game_camera_param_manager(q) == 1) {
            GAMEUTIL_reset_interp_ratio_cntrl(p);
            GAMEUTIL_set_param_interp_ratio_cntrl(p, 0.0f, get_interp_time_game_camera_param_manager(q));
            *(float *)(cn + 0x38) = *(float *)(cn + 0x40);
            *(float *)(cn + 0x3C) = *(float *)(cn + 0x44);
        }
        aim1 = cn + 0x10;
        set_interp_param_aim_angle_interp_cntrl(aim1, *(float *)(*(char **)cam + 0xB8), *(float *)(*(char **)cam + 0xBC) * 0.017453294f);
        aim2 = cn + 0x20;
        set_interp_param_aim_angle_interp_cntrl(aim2, *(float *)(*(char **)cam + 0xC0), *(float *)(*(char **)cam + 0xC4) * 0.017453294f);
        if (GAMEUTIL_get_cur_status_status_manager(cn) == 2) {
            if (GAMEUTIL_is_status_change_status_manager(cn) == 1) {
                s6 = 1;
                fp = 1;
            }
        }
        if (fp == 1 || *(int *)(cam + 0xF38) == 0)
            reset_aim_angle_interp_cntrl(aim1, *(float *)(cn + 0x30));
        else
            doit_aim_angle_interp_cntrl(aim1, *(float *)(cn + 0x30), *(float *)(s7 + 0x30), 0, dt);
        if (is_cut_default_pitch_interp_camera_target_approach(cam + 0x6A0) == 1)
            s6 = 1;
        if (s6 == 1 || *(int *)(cam + 0xF3C) == 0)
            reset_aim_angle_interp_cntrl(aim2, *(float *)(cn + 0x34));
        else
            doit_aim_angle_interp_cntrl(aim2, *(float *)(cn + 0x34), *(float *)(s7 + 0x34), 0, dt);
        if (*(int *)(*(char **)cam + 0xB4) == 0 || GAMEUTIL_get_cur_status_status_manager(cn) == 2)
            GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(p);
        GAMEUTIL_doit_interp_ratio_cntrl(p, dt);
    }
    func_000D6C88(cn, cam);
}
