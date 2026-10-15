extern int get_game_camera_cur_mode(void);

int CAM_is_need_obstacle_avoid_ofst(char *p)
{
    int mode = get_game_camera_cur_mode();
    if (mode == 1 && *(int *)(*(char **)(p + 0x2C44) + 0xA8) == mode && *(int *)(p + 0x2AC8) == *(int *)(*(char **)(p + 0x2C44) + 0xA8))
        return 1;
    return 0;
}
