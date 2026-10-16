extern float CAM_get_interp_ratio_by_time(int, float, float, float, float);

float get_interp_ratio_game_camera_param_manager(char *m)
{
    float t = *(float *)(m + 0x20);

    return CAM_get_interp_ratio_by_time(1, t < 0.0f ? *(float *)(m + 0x66C) : 1.0f, *(float *)(m + 0x4),
                                        t < 0.0f ? *(float *)(m + 0x670) : t, 0.0f);
}
