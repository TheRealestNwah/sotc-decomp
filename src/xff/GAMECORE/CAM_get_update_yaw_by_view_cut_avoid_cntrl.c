extern void GAMEUTIL_set_param_extend_interp_ratio_cntrl(void *, float, float, float);
extern float CAM_doit_aim_angle_rot(void *, int, float, float, float, float, float, float, float, float, float);
static inline void setExtendedCommon(char *control, float start, float value, float time)
{
    if (*(int *)(control + 0x20) == 0)
        GAMEUTIL_set_param_extend_interp_ratio_cntrl(control + 0x24, start, value, time);
}
float CAM_get_update_yaw_by_view_cut_avoid_cntrl(char *control, void *unused, char **parameters,
                                               float from, float aim, float delta)
{
    char *rotation = control + 0xC;
    char *parameter = *parameters;
    int on = *(int *)control == 1;
    setExtendedCommon(rotation, *(float *)(control + 0x94),
                      *(float *)(parameter + 0x74), *(float *)(parameter + 0x78));
    return CAM_doit_aim_angle_rot(rotation, on, from, aim, 0.0f, 0.0f,
                                 *(float *)(parameter + 0x7C), *(float *)(parameter + 0x80),
                                 *(float *)(parameter + 0x84), *(float *)(parameter + 0x88), delta);
}
