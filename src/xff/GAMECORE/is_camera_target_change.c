int is_camera_target_change(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x1C)) != (*(int *)((char *)(arg0) + 0x18));
}
