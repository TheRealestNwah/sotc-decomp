extern int GAMEUTIL_get_cur_status_status_manager();
extern int GAMEUTIL_is_status_change_status_manager(int);

int is_cut_default_pitch_interp_camera_target_approach(int arg0)
{
    int temp_v0;
    int var_v0;

    temp_v0 = GAMEUTIL_get_cur_status_status_manager();
    if ((temp_v0 != 1) || (var_v0 = GAMEUTIL_is_status_change_status_manager(arg0), (var_v0 != temp_v0))) {
        var_v0 = 0;
    }
    return var_v0;
}
