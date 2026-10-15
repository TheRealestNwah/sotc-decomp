float GAMEUTIL_mul_ratio(int clamp, float a, float r)
{
    if (clamp != 0) {
        if (r <= 0.0f)
            return 0.0f;
        if (1.0f <= r)
            return a;
    }
    return r * a;
}
