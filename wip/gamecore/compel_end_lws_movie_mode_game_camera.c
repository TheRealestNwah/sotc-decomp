extern char *get_game_camera(int);
extern void *get_main_type_camera_lws_animation(void);
extern int get_camera_lws_animation_param(int);
extern void end_camera_lws_animation_by_paramID(int);

static inline int is_playing_lws_movie_now_game_camera(int manager)
{
    if (*(int *)(get_game_camera(manager) + 0x1360) == 8 || get_main_type_camera_lws_animation())
        return 1;
    return 0;
}

int compel_end_lws_movie_mode_game_camera(int manager)
{
    char *work = get_game_camera(manager) + 0x34E0;

    if (is_playing_lws_movie_now_game_camera(manager) == 1) {
        if (*(int *)(work + 0x90) != 0) {
            end_camera_lws_animation_by_paramID(get_camera_lws_animation_param(*(int *)(work + 0x90)));
            *(int *)(work + 0xF8) = 0;
        }
        return 1;
    }
    return 0;
}
