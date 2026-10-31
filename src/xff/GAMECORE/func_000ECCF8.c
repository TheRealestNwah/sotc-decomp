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

static void func_000ECCF8(char *obj, char *camera)
{
    if (resetOrMovieOrCutout(camera) == 1) {
        *(int *)(obj + 0x182C) = 0;
    } else if (*(int *)(obj + 0x1838) == 1) {
        *(int *)(obj + 0x182C) = 0;
    } else if (*(int *)(obj + 0x1838) == 2) {
        *(int *)(obj + 0x182C) += 1;
    }
    if (*(int *)(obj + 0x182C) >= 10) {
        *(int *)(camera + 0x2C40) = 5;
    }
}
