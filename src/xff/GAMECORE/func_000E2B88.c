extern float get_view_angle_lws_anime_mode_base(void *);

static float func_000E2B88(int mode, char *p, void *lws)
{
    if (mode == 1) {
        return get_view_angle_lws_anime_mode_base(lws);
    }
    return *(float *)(p + 0x4C);
}
