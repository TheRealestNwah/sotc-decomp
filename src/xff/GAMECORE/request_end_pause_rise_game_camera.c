extern int request_end_camera_pause_rise();

int request_end_pause_rise_game_camera(int a, int b, int c, int d)
{
    return request_end_camera_pause_rise(a + 14160, a, b, d);
}
