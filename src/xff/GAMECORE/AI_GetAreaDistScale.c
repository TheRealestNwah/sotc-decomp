float AI_GetAreaDistScale(float fparg0, float fparg1)
{
    float temp_f0;
    float var_f0;

    var_f0 = fparg0;
    if (!(fparg0 < fparg1)) {
        var_f0 = fparg1;
    }
    temp_f0 = var_f0 / fparg0;
    return temp_f0 * temp_f0;
}
