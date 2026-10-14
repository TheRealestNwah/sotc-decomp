extern int D_0017B738;
extern int GAMEUTIL_is_push_or_down_1p_button(int, int);

int is_view_angle_zoom_game_camera(void)
{
    return GAMEUTIL_is_push_or_down_1p_button(0, D_0017B738) == 1;
}
