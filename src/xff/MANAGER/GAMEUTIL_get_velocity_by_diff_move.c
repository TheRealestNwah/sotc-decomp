float GAMEUTIL_get_velocity_by_diff_move(int arg0, float fparg0, float fparg1, float fparg2, float fparg3)
{
    float var_f0;

    var_f0 = fparg0;
    if (fparg3 != 0.0f) {
        var_f0 = (fparg2 - fparg1) / fparg3;
        if ((arg0 != 0) && (var_f0 < 0.0f)) {
            var_f0 = -var_f0;
        }
    }
    return var_f0;
}
