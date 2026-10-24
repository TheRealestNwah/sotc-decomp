extern float func_0000E158(void *, float);
extern float func_0000E198(void *, float);
extern float GAMEUTIL_increase_pitch_limit_clip(int, int, float, float, float, float);

static inline float clip_pitch(void *cntrl, float pitch)
{
    float max = func_0000E158(cntrl, 0.0f);
    float min = func_0000E198(cntrl, 0.0f);

    return GAMEUTIL_increase_pitch_limit_clip(0, 0, pitch, 0.0f, max, min);
}

float get_max_min_clip_base_pitch_nico_yaw_pitch_cntrl(void *cntrl, float pitch)
{
    return clip_pitch(cntrl, pitch);
}
