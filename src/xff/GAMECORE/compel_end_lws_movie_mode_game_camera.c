extern char *get_game_camera(int);
extern int get_main_type_camera_lws_animation();
extern int get_camera_lws_animation_param(int);
extern void end_camera_lws_animation_by_paramID(int);

int compel_end_lws_movie_mode_game_camera(int id)
{
    char *base = get_game_camera(id) + 0x34E0;
    register int hit __asm__("$3");

    {
        int type = *(int *)(get_game_camera(id) + 0x1360);
        register int lws __asm__("$2");

        lws = 8;
        if (type == lws || get_main_type_camera_lws_animation() != 0)
            hit = 1;
        else
            hit = 0;
    }
    {
        register int one __asm__("$2") = 1;

        if (hit == one) {
            int cur = *(int *)(base + 0x90);

            if (cur != 0) {
                end_camera_lws_animation_by_paramID(get_camera_lws_animation_param(cur));
                *(int *)(base + 0xF8) = 0;
            }
            return 1;
        }
    }
    return 0;
}
