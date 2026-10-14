extern float GAMEUTIL_increase_yaw(int, float, float);

float GAMEUTIL_get_increase_value(int mode, float a, float b)
{
    if (mode == 1)
        return GAMEUTIL_increase_yaw(0, a, b);
    return a + b;
}
