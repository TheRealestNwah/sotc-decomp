extern float acosf(float);

float iosGetACosfExact(float x)
{
    if (x >= 1.0f) {
        return 0.0f;
    }
    if (x <= -1.0f) {
        return 3.1415927f;
    }
    return acosf(x);
}
