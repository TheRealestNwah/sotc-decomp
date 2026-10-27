extern float GAMEUTIL_increase_yaw(int *, float, float);
extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(void *, float, float);

void get_radiate_direction_nico_sight_on(void *out, char *p)
{
    float yaw = GAMEUTIL_increase_yaw(0, *(float *)(p + 0x280), *(float *)(p + 0x248));
    float pitch = GAMEUTIL_increase_pitch(0, 0, *(float *)(p + 0x284), 0.0f, 1.483529806137085f, -1.483529806137085f);

    GAMEUTIL_get_direction_by_yaw_pitch(out, yaw, pitch);
}
