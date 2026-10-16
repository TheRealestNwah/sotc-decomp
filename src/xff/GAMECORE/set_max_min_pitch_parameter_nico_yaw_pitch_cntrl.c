extern float GAMEUTIL_increase_pitch_limit_clip(int, int, float, float, float, float);

void set_max_min_pitch_parameter_nico_yaw_pitch_cntrl(char *c, float max, float min)
{
    *(float *)(c + 0x11C) = 0.0f;
    *(float *)(c + 0x120) = GAMEUTIL_increase_pitch_limit_clip(0, 0, *(float *)(c + 0x11C), max * 0.017453293f, 1.483529806137085f, -1.483529806137085f);
    *(float *)(c + 0x124) = GAMEUTIL_increase_pitch_limit_clip(0, 0, *(float *)(c + 0x11C), min * 0.017453293f, 1.483529806137085f, -1.483529806137085f);
}
