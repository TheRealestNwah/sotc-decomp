extern void GAMEUTIL_is_between_pitch_and_pitch();
extern void GAMEUTIL_is_between_yaw_and_yaw();

void GAMEUTIL_is_between_value(int arg0)
{
    if (arg0 == 1) {
        GAMEUTIL_is_between_yaw_and_yaw();
        return;
    }
    GAMEUTIL_is_between_pitch_and_pitch();
}
