float AI_GetAreaDistScale2(float fparg0, float fparg1)
{
    float var_f0;

    var_f0 = fparg0;
    if (!(fparg0 < fparg1)) {
        var_f0 = fparg1;
    }
    return var_f0 / fparg0;
}
