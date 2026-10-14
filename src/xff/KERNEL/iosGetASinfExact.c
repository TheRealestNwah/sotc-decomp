extern float asinf(float);

float iosGetASinfExact(float x)
{
    if (x >= 1.0f) {
        return 1.5707963f;
    }
    if (x <= -1.0f) {
        return -1.5707963f;
    }
    return asinf(x);
}
