int get_motion_data_camera_lws_animation(char *p)
{
    if (p == 0) {
        return 0;
    }
    return *(int *)(p + 0x44);
}
