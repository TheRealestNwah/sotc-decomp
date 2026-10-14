extern int is_pass_camera_etc_condition();

int is_hit_leave_plane_game_camera(int a, int b, int c, int d)
{
    return is_pass_camera_etc_condition(3, a + 16, c, d);
}
