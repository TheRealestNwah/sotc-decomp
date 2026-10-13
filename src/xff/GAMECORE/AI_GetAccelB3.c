float AI_GetAccelB3(float fparg0, float fparg1, float fparg2, float fparg3, float fparg4, float fparg5)
{
    float var_f16;

    var_f16 = fparg4;
    if (var_f16 < 0.0333667f) {
        var_f16 = 0.0333667f;
    }
    return (6.0f / (var_f16 * var_f16)) * (((((4.0f / var_f16) * (fparg3 - fparg2)) - fparg1) - (fparg0 * 3.0f)) - (fparg5 * var_f16));
}
