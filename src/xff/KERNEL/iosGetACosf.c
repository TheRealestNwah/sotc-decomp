float iosGetACosf(float x)
{
    float x3;
    float x5;
    float x7;

    x3 = x * x * x;
    x5 = x3 * x * x;
    x7 = x5 * x * x;
    return 1.5707963f - x - x3 * 0.16666666f - x5 * 0.075f - x7 * 0.044642855f
         - x7 * x * x * 0.030381943f;
}
