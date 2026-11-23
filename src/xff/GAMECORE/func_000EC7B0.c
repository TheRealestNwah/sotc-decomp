extern void CAM_init_aim_angle_rot(char *, int);
extern void CAM_init_camera_warp_cntrl(char *, int, int, int);
static void func_000EC7B0(char *self, char *c)
{
    char *a = c + 0x4;

    CAM_init_aim_angle_rot(a, 0);
    CAM_init_aim_angle_rot(c + 0x48, 1);
    *(int *)(a + 0x88) = 0;
    *(int *)(a + 0x8C) = 0;
    CAM_init_camera_warp_cntrl(self + 0x1840, 2, 3, 0);
    *(int *)(c + 0x94) = 1;
}
