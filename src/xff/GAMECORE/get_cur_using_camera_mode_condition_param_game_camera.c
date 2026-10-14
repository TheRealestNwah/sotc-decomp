extern int get_cur_base_mode_condition_game_camera_param_manager();

int get_cur_using_camera_mode_condition_param_game_camera(int a, int b, int c, int d)
{
    return get_cur_base_mode_condition_game_camera_param_manager(a + 80, b, c, d);
}
