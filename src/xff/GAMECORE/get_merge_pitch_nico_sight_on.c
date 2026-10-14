extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);

float get_merge_pitch_nico_sight_on(char *p)
{
    return GAMEUTIL_increase_pitch(0, 0, *(float *)(p + 0x284), 0.0f, 1.48352985f, -1.48352985f);
}
