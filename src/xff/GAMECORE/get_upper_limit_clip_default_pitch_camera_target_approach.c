extern int GAMEUTIL_get_cur_status_status_manager();

float get_upper_limit_clip_default_pitch_camera_target_approach(float fparg0)
{
    float var_f20;

    var_f20 = fparg0;
    if ((GAMEUTIL_get_cur_status_status_manager() == 1) && (var_f20 > -1.4835298061370849609375f)) {
        var_f20 = -1.4835298061370849609375f;
    }
    return var_f20;
}
