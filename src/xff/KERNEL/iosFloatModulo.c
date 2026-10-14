float iosFloatModulo(float a, float b)
{
    if (b == 0.0f)
        return 0.0f;
    return a - b * (float)(int)(a / b);
}
