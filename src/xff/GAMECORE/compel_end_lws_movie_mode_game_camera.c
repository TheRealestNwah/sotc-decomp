extern char *get_game_camera(int);
extern int get_main_type_camera_lws_animation();
extern int get_camera_lws_animation_param(int);
extern void end_camera_lws_animation_by_paramID(int);

#ifdef NONMATCHING
/* Parked: 8 words differ (register allocation/scheduling); permuter found no zero. */
int compel_end_lws_movie_mode_game_camera(int id)
{
    char *base = get_game_camera(id) + 0x34E0;
    int hit;

    if (*(int *)(get_game_camera(id) + 0x1360) == 8 || get_main_type_camera_lws_animation() != 0)
        hit = 1;
    else
        hit = 0;
    if (hit == 1) {
        int cur = *(int *)(base + 0x90);
        if (cur != 0) {
            end_camera_lws_animation_by_paramID(get_camera_lws_animation_param(cur));
            *(int *)(base + 0xF8) = 0;
        }
        return 1;
    }
    return 0;
}
#else
int compel_end_lws_movie_mode_game_camera(int id);
#endif
