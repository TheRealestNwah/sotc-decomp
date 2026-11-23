extern void CAM_init_aim_angle_rot(char *, int);
extern void CAM_init_camera_warp_cntrl(char *, int, int, int);
extern void reset_pitch_rot_cntrl_camera_target_approach(char *);
static void func_000EC740(char *self, char *c)
{
    CAM_init_aim_angle_rot(c + 0x4, 0);
    CAM_init_aim_angle_rot(c + 0x48, 1);
    CAM_init_aim_angle_rot(c + 0x8C, 1);
    *(int *)(c + 0xD0) = 0;
    CAM_init_camera_warp_cntrl(self + 0x1840, 2, 3, 1);
    reset_pitch_rot_cntrl_camera_target_approach(self + 0x6A0);
}
