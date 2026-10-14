extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern float func_000E15F8(float, float);
extern float powf(float, float);

float CAM_get_yaw_velocity(float a, float b, float target, float cur, float range, float exp)
{
    float limit = range * 0.5f;
    float t = target * 0.0174532925f;
    float c = cur * 0.0174532925f;
    float d;
    float delta;

    limit *= 0.0174532925f;
    d = GAMEUTIL_get_difference_yaw_and_yaw(a, b);
    delta = t - c;
    return c + delta * powf(func_000E15F8(d, limit), exp);
}
