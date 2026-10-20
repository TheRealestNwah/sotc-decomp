extern void CAM_reset_aim_angle_rot(void *);
void reset_pitch_rot_cntrl_camera_target_approach(char *control)
{
    CAM_reset_aim_angle_rot(control + 0x44);
}
