float GAMEUTIL_get_difference_yaw_and_yaw(float a, float b)
{
    float d = b - a;
    if (d < 0.0f)
        d = -d;
    if (3.1415926f < d)
        d = 6.2831852f - d;
    return d;
}
