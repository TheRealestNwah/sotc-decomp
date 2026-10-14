extern char *get_game_camera();

void set_post_boss_dead_playable_flag_camera_etc_condition(int a, int b)
{
    *(int *)(get_game_camera(a) + 0x18) = b;
}
