extern float GAMEUTIL_get_new_velocity_by_brake_abs(float, float);

float GAMEUTIL_get_new_velocity_by_brake(float v, float b)
{
    float r = GAMEUTIL_get_new_velocity_by_brake_abs(v < 0.0f ? -v : v, b);
    if (v >= 0.0f) return r;
    return -r;
}
