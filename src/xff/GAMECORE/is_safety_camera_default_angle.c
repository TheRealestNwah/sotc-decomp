extern int GAMEUTIL_get_cur_status_status_manager(int *);

int is_safety_camera_default_angle(int *status)
{
    return GAMEUTIL_get_cur_status_status_manager(status) != 1;
}
