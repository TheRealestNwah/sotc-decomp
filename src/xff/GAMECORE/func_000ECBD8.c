extern void reset_camera_collision_data_except_slide_move_ratio(void *);

static void func_000ECBD8(char *cam)
{
    *(int *)(cam + 0x18C0) = 0;
    *(int *)(cam + 0x18C4) = 0;
    *(int *)(cam + 0x18C8) = 0;
    reset_camera_collision_data_except_slide_move_ratio(cam + 0x17B0);
}
