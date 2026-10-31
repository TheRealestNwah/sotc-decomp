extern void CAM_init_aim_angle_rot(void *, int);

static void func_000EB980(char *c, int reset)
{
    if (reset == 1)
        *(int *)c = 0;
    CAM_init_aim_angle_rot(c + 4, 0);
    CAM_init_aim_angle_rot(c + 0x48, 1);
    CAM_init_aim_angle_rot(c + 0x8C, 1);
    *(int *)(c + 0xD0) = 0;
}
