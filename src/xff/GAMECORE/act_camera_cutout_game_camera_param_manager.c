int act_camera_cutout_game_camera_param_manager(int *param, char *camera)
{
    int mode = param[2];

    if (mode == 1 && *(int *)(camera + 0x1360) == mode) {
        return 1;
    }
    return 0;
}
