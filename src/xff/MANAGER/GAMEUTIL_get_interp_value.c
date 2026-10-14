float GAMEUTIL_get_interp_value(float a, float b, float t)
{
    if (t <= 0.0f) return b;
    if (t >= 1.0f) return a;
    if (a == b) return a;
    return (t * a) + ((1.0f - t) * b);
}