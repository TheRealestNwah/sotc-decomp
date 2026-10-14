extern float GAMEUTIL_increase_yaw(int, float, float);

float get_merge_yaw_nico_sight_on(char *p)
{
    return GAMEUTIL_increase_yaw(0, *(float *)(p + 0x280), *(float *)(p + 0x248));
}
