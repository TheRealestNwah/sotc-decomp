float AI_GetAccelA3(float fparg0, float fparg1, float fparg2, float fparg3, float fparg4, float fparg5)
{
    float temp_f3;
    float var_f16;

    var_f16 = fparg4;
    if (var_f16 < 0.0333667f) {
        var_f16 = 0.0333667f;
    }
    temp_f3 = var_f16 * var_f16;
    return (-2.0f / temp_f3) * (((((6.0f / temp_f3) * (fparg2 - fparg1)) - (2.0f * fparg5)) - ((6.0f / var_f16) * fparg0)) - fparg3);
}
