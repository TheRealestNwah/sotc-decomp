extern void CAM_init_camera_warp_cntrl(void *, int, int, int);

static void func_000ECBA0(char *cam)
{
    *(int *)(cam + 0x1830) = 0;
    *(int *)(cam + 0x1834) = 0;
    *(int *)(cam + 0x1838) = 0;
    CAM_init_camera_warp_cntrl(cam + 0x1840, 0, 0, 0);
}
