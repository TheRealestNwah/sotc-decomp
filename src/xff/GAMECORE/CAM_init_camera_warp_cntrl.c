extern void CAM_reset_camera_warp_cntrl(void *control);

void CAM_init_camera_warp_cntrl(void *arg0, int arg1, int arg2, int arg3) {
    (*(int *)((char *)(arg0) + 0)) = arg1;
    (*(float *)((char *)(arg0) + 0x14)) = 0.087266461f;
    (*(int *)((char *)(arg0) + 0xC)) = arg2;
    (*(int *)((char *)(arg0) + 0x1C)) = arg3;
    (*(float *)((char *)(arg0) + 0x18)) = 0.087266461f;
    CAM_reset_camera_warp_cntrl(arg0);
}
