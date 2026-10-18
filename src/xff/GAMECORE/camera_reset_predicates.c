extern int act_camera_cutout_game_camera_param_manager(int *, char *);

static inline int resetOrMovieOrCutout(char *camera)
{
    int mode = *(int *)(camera + 0x1360);
    int reset;
    if (mode == 0 || mode == 8)
        reset = 1;
    else
        reset = 0;
    if (reset == 1 || act_camera_cutout_game_camera_param_manager((int *)(camera + 0x50), camera) == 1)
        return 1;
    return 0;
}

int is_reset_or_lws_movie_or_cutout_game_camera(void *object)
{
    char *camera = object;
    int mode = *(int *)(camera + 0x1360);
    int reset;
    if (mode == 0 || mode == 8)
        reset = 1;
    else
        reset = 0;
    if (reset == 1 || act_camera_cutout_game_camera_param_manager((int *)(camera + 0x50), camera) == 1)
        return 1;
    return 0;
}

int is_reset_or_lws_fixed_point_or_lws_movie_or_cutout_game_camera(void *object)
{
    char *camera = object;
    if (resetOrMovieOrCutout(camera) == 1 || *(int *)(camera + 0x1360) == 7)
        return 1;
    return 0;
}
