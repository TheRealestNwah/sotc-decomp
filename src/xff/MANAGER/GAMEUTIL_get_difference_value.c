extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);

float GAMEUTIL_get_difference_value(int mode, float a, float b)
{
    if (mode == 1)
        return GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(a, b);
    return b - a;
}
