extern int get_game_camera(int);

int is_mode_change_game_camera(int owner)
{
    void *temp_v0;

    temp_v0 = (void *)get_game_camera(owner);
    return (*(int *)((char *)(temp_v0) + 0x1360)) != (*(int *)((char *)(temp_v0) + 0x1364));
}
