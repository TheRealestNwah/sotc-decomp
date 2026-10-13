int change_camera_target(void *arg0, int arg1)
{
    if (arg1 != 0) {
        (*(int *)((char *)(arg0) + 0x1C)) = arg1;
        return 1;
    }
    return 0;
}
