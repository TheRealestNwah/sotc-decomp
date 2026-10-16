extern int GAMEUTIL_get_cur_status_status_manager(void *);
extern void CAM_set_interp_param_aim_rot_common(void *, float, float);
extern float CAM_doit_aim_angle_rot(void *, int, float, float, float, float, float, float, float, float, float);

float act_pitch_rot_camera_target_approach(char *c, float pitch, float aim, float dt)
{
    int on = GAMEUTIL_get_cur_status_status_manager(c) == 1;

    CAM_set_interp_param_aim_rot_common(c + 0x44, 0.0f, 0.3f);
    return CAM_doit_aim_angle_rot(c + 0x44, on, pitch, aim, 0.0f, 0.0f, 100.0f, 1.0f, 40.0f, 0.8f, dt);
}
