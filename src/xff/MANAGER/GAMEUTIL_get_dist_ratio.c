float GAMEUTIL_get_dist_ratio(float fparg0, float fparg1, float fparg2)
{
    float var_f0;

    var_f0 = 0.0f;
    if (!(fparg0 <= fparg1)) {
        var_f0 = 1.0f;
        if (!(fparg2 <= fparg0)) {
            var_f0 = (fparg0 - fparg1) / (fparg2 - fparg1);
        }
    }
    return var_f0;
}
