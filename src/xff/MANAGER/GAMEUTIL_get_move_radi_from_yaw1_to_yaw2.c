float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float a, float b)
{
    float d = b - a;
    int pos;
    if (d < 0.0f)
        d = -d;
    pos = 1;
    if (b < a)
        pos = 0;
    if (3.1415926f < d) {
        pos = !pos;
        d = 6.2831852f - d;
    }
    if (pos)
        return d;
    return -d;
}
