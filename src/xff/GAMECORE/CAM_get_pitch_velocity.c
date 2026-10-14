extern float GAMEUTIL_get_difference_pitch_and_pitch(float, float);
extern float powf(float, float);

float CAM_get_pitch_velocity(float a, float b, float target, float cur, float range, float exp)
{
    float half = range * 0.5f;
    float c = cur * 0.0174532925f;
    float t = target * 0.0174532925f;
    float limit = half * 0.0174532925f;
    float d = GAMEUTIL_get_difference_pitch_and_pitch(a, b);
    float r = (limit <= d) ? 1.0f : d / limit;

    return c + (t - c) * powf(r, exp);
}
