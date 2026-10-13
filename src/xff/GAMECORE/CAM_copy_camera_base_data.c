void CAM_copy_camera_base_data(void *arg0, void *arg1)
{
    (*(long *)((char *)(arg0) + 0)) = (long) (*(long *)((char *)(arg1) + 0));
    (*(long *)((char *)(arg0) + 8)) = (long) (*(long *)((char *)(arg1) + 8));
    (*(long *)((char *)(arg0) + 0x10)) = (long) (*(long *)((char *)(arg1) + 0x10));
    (*(long *)((char *)(arg0) + 0x18)) = (long) (*(long *)((char *)(arg1) + 0x18));
    (*(long *)((char *)(arg0) + 0x20)) = (long) (*(long *)((char *)(arg1) + 0x20));
    (*(long *)((char *)(arg0) + 0x28)) = (long) (*(long *)((char *)(arg1) + 0x28));
}
