extern void GAMEUTIL_set_param_extend_interp_ratio_cntrl(void *, float, float, float);
extern float CAM_doit_aim_angle_rot(void *, int, float, float, float, float, float, float, float, float, float);
static inline void setExtendedCommon(char *control, float start, float value, float time)
{
    if (*(int *)(control + 0x20) == 0)
        GAMEUTIL_set_param_extend_interp_ratio_cntrl(control + 0x24, start, value, time);
}
extern int get_cur_attr_camera_default_angle(int *);
extern int get_attr_camera_target_lost_angle(int *);
float CAM_get_update_pitch_by_view_cut_avoid_cntrl(char *control, char *camera, char **parameters,
                                                 float from, float aim, float delta)
{
    char *rotation = control + 0x50;
    char *parameter = *parameters;
    int on = 0;
    if (*(int *)control == 1) {
        int attribute = get_cur_attr_camera_default_angle((int *)(camera + 0x730));
        if (attribute != 2 || get_attr_camera_target_lost_angle((int *)(camera + 0x660)) == 2)
            on = 1;
    }
    setExtendedCommon(control + 0x50, *(float *)(control + 0x98),
                      *(float *)(parameter + 0x90), *(float *)(parameter + 0x94));
    return CAM_doit_aim_angle_rot(rotation, on, from, aim, 0.0f, 0.0f,
                                 *(float *)(parameter + 0x98), *(float *)(parameter + 0x9C),
                                 *(float *)(parameter + 0xA0), *(float *)(parameter + 0xA4), delta);
}
