extern float GAMEUTIL_increase_yaw_limit_clip_extend(int *moved, int upperEnabled, int lowerEnabled,
    int option, float yaw, float delta, float upper, float lower);

float GAMEUTIL_increase_yaw_limit_clip(int *moved, int option, float yaw, float delta,
                                     float upper, float lower)
{
    return GAMEUTIL_increase_yaw_limit_clip_extend(moved, 1, 1, option, yaw, delta, upper, lower);
}
