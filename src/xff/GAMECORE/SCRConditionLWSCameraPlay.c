extern int get_main_cameraman(void);
extern int is_playing_lws_movie_now_game_camera(int);

int SCRConditionLWSCameraPlay(void)
{
    return is_playing_lws_movie_now_game_camera(get_main_cameraman());
}
