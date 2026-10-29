extern int GAMEUTIL_is_between_pitch_and_pitch(float, float, float);
extern int GAMEUTIL_is_between_yaw_and_yaw(float, float, float);

int GAMEUTIL_is_between_value(int mode, float value, float first, float second)
{
    if (mode == 1)
        return GAMEUTIL_is_between_yaw_and_yaw(value, first, second);
    return GAMEUTIL_is_between_pitch_and_pitch(value, first, second);
}
