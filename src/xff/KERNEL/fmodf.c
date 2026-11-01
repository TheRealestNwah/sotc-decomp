extern float __ieee754_fmodf(float x, float y);

float fmodf(float x, float y)
{
    return __ieee754_fmodf(x, y);
}
