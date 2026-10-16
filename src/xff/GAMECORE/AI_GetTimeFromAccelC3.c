static inline float sqrtF(float x)
{
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

float AI_GetTimeFromAccelC3(float a, float b, float c, float d)
{
    float disc;

    if (d < 0.099999997f)
        d = 0.099999997f;
    b = b + a;
    if (c < 0.0f)
        c = -c;
    disc = b * 9.0f * b + d * 12.0f * c;
    if (disc < 0.0f)
        return 0.0f;
    return (b * -3.0f + sqrtF(disc)) / d;
}
