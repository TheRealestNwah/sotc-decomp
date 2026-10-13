void reset_game_camera_standby_flag(void *arg0)
{
    (*(int *)((char *)(arg0) + 4)) = 0;
}
