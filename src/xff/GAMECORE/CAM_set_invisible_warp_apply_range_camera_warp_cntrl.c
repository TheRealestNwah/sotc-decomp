void CAM_set_invisible_warp_apply_range_camera_warp_cntrl(char *p, float f1, float f2)
{
    *(float *)(p + 0x14) = f1;
    *(float *)(p + 0x18) = f2;
}
