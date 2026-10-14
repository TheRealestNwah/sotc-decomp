int GAMEUTIL_is_nearly_equal_pitch(float fparg0, float fparg1, float fparg2)
{
    float var_f13;
    int var_v0;

    var_f13 = fparg1 - fparg0;
    if (var_f13 < 0.0f) {
        var_f13 = -var_f13;
    }
    var_v0 = 1;
    if (!(var_f13 <= fparg2)) {
        var_v0 = 0;
    }
    return var_v0;
}
