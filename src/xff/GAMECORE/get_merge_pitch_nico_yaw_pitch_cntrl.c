extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);

float get_merge_pitch_nico_yaw_pitch_cntrl(char *p)
{
    return GAMEUTIL_increase_pitch(0, 0, *(float *)(p + 0x68), *(float *)(p + 0x50), *(float *)(p + 0x120), *(float *)(p + 0x124));
}
