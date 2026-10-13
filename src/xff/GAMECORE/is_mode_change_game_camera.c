extern void *get_game_camera();

int is_mode_change_game_camera(void)
{
    void *temp_v0;

    temp_v0 = get_game_camera();
    return (*(int *)((char *)(temp_v0) + 0x1360)) != (*(int *)((char *)(temp_v0) + 0x1364));
}
