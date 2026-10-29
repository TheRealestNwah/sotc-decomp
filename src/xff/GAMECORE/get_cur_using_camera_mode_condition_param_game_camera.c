extern int get_cur_base_mode_condition_game_camera_param_manager(void *);

int get_cur_using_camera_mode_condition_param_game_camera(char *work)
{
    return get_cur_base_mode_condition_game_camera_param_manager((void *)(work + 80));
}
