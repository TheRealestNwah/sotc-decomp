int is_game_camera_mode_now(void *arg0)
{
    return (unsigned int) (*(unsigned int *)((char *)(arg0) + 4)) < 2U;
}
