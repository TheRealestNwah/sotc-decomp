void request_end_camera_pause_rise(void *arg0)
{
    (*(int *)((char *)(arg0) + 4)) = 0;
    (*(int *)((char *)(arg0) + 0)) = 2;
}
