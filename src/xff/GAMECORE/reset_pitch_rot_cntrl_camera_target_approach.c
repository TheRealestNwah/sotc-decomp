extern int CAM_reset_aim_angle_rot();

int reset_pitch_rot_cntrl_camera_target_approach(int a, int b, int c, int d)
{
    return CAM_reset_aim_angle_rot(a + 68, b, c, d);
}
