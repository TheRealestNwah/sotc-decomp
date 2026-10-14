extern const float RO_00181080;

void CAM_reset_camera_warp_cntrl(void *work)
{
    *(int *)((char *)work + 4) = 0;
    *(int *)((char *)work + 8) = 0;
    *(int *)((char *)work + 0x10) = 0;
    *(int *)((char *)work + 0x20) = 0;
    *(int *)((char *)work + 0x24) = 0;
    *(int *)((char *)work + 0x28) = 0;
    *(int *)((char *)work + 0x2C) = 0;
    *(float *)((char *)work + 0x30) = *(float *)((char *)work + 0x34) =
        *(float *)((char *)work + 0x38) = RO_00181080;
    *(float *)((char *)work + 0x3C) = 1.0f;
}
