float GAMEUTIL_get_difference_pitch_and_pitch(float fparg0, float fparg1)
{
    float var_f13;

    var_f13 = fparg1 - fparg0;
    if (var_f13 < 0.0f) {
        var_f13 = -var_f13;
    }
    return var_f13;
}
