int is_loop_camera_lws_animation(void *arg0)
{
    return ((*(int *)((char *)(arg0) + 0x10)) & 7) != 0;
}
