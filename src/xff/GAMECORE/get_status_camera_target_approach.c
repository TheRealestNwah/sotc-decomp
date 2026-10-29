extern int GAMEUTIL_get_cur_status_status_manager(int *);

int get_status_camera_target_approach(char *work)
{
    return GAMEUTIL_get_cur_status_status_manager((int *)(work + 0));
}
