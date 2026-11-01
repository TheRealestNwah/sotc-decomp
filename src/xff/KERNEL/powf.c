extern float __ieee754_powf(float x, float y);

float powf(float x, float y)
{
    return __ieee754_powf(x, y);
}
