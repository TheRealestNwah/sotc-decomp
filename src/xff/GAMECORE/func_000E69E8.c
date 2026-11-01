extern float D_0017B720[];
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_increase_yaw(int *, float, float);
extern float GAMEUTIL_increase_pitch(int *, float, float, float, float, int);
extern void GAMEUTIL_get_direction_by_yaw_pitch(float *, float, float);
extern void CAM_get_camera_position_by_look_at(float *, float *, float *, float);

static void func_000E69E8(char *o)
{
    float *look = (float *)(o + 0xA0);
    float *dir = (float *)(o + 0xC0);
    int clip[2];
    float rate;
    float yaw_rate;

    clip[0] = 0;
    clip[1] = 0;
    rate = 1.0f - GAMEUTIL_get_dist_ratio(*(float *)(o + 0x228) + D_0017B720[0], 0.0f, 0.3f);
    yaw_rate = rate * *(float *)(o + 0x22C);
    rate = rate * *(float *)(o + 0x230);
    look[12] = GAMEUTIL_increase_yaw(&clip[0], look[12], yaw_rate * D_0017B720[0]);
    look[13] = GAMEUTIL_increase_pitch(&clip[1], look[13], rate * D_0017B720[0], 1.48352985f, -1.48352985f, 0);
    if (clip[0] || clip[1]) {
        GAMEUTIL_get_direction_by_yaw_pitch(dir, look[12], look[13]);
        CAM_get_camera_position_by_look_at(look, dir, (float *)(o + 0xB0), look[14]);
    }
}
