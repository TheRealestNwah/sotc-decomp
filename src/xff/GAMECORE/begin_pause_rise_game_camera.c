extern void init_camera_pause_rise(void *, void *, int);

void begin_pause_rise_game_camera(int *c, int a)
{
    if (c[0] == 2)
        return;
    c[0] = 2;
    init_camera_pause_rise((char *)c + 0x3750, c, a);
}
