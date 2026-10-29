extern char *get_game_camera(void *);
void set_post_boss_dead_playable_flag_camera_etc_condition(void *object, int flag)
{
    *(int *)(get_game_camera(object) + 0x18) = flag;
}
