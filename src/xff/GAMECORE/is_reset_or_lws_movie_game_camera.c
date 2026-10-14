int is_reset_or_lws_movie_game_camera(char *p)
{
    int m = *(int *)(p + 0x1360);

    if (m == 0 || m == 8) {
        return 1;
    }
    return 0;
}
