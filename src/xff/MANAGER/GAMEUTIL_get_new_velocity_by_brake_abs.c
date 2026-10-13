float GAMEUTIL_get_new_velocity_by_brake_abs(float fparg0, float fparg1, float fparg2, float fparg3)
{
    float var_f0;

    var_f0 = fparg2;
    if (fparg1 >= 0.0f) {
        var_f0 = fparg0 - (fparg1 * fparg3);
        if (var_f0 < fparg2) {
            var_f0 = fparg2;
        }
    }
    return var_f0;
}
