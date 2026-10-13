float AI_GetAccelC3(float fparg0, float fparg1, float fparg2, float fparg3, float fparg4, float fparg5)
{
    float var_f17;

    var_f17 = fparg5;
    if (var_f17 < 0.0333667f) {
        var_f17 = 0.0333667f;
    }
    return ((((12.0f / var_f17) * (fparg3 - fparg2)) - ((fparg1 + fparg0) * 6.0f)) + (fparg4 * var_f17)) / var_f17;
}
