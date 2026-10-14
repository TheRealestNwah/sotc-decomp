int is_fixed_point_type_camera_lws_animation(void *arg0)
{
    return (((unsigned int) (*(unsigned int *)((char *)(arg0) + 0x10)) >> 3) & 7) == 3;
}
