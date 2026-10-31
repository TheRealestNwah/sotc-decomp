extern int is_view_angle_zoom_game_camera(void *);

static float func_000E2BB8(int which, char *cam, char *p)
{
    float r = 1.0f;
    int z = is_view_angle_zoom_game_camera(cam);

    if (z == 1) {
        if (which == z)
            r = *(float *)(p + 0xB4);
        else
            r = *(float *)(cam + 0x13C0);
    }
    return r;
}
