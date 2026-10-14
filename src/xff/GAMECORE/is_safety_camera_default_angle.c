extern int GAMEUTIL_get_cur_status_status_manager();

int is_safety_camera_default_angle(void)
{
    return GAMEUTIL_get_cur_status_status_manager() != 1;
}
