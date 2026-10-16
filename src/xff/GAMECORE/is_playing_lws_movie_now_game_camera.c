extern char *get_game_camera(void);
extern int get_main_type_camera_lws_animation(void);

int is_playing_lws_movie_now_game_camera(void)
{
    if (*(int *)(get_game_camera() + 0x1360) == 8 || get_main_type_camera_lws_animation())
        return 1;
    return 0;
}
