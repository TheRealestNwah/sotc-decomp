extern int is_end_camera_pause_rise(int *);

int is_end_pause_rise_game_camera(char *work)
{
    return is_end_camera_pause_rise((int *)(work + 14160));
}
