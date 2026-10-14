int GAMEUTIL_is_nearly_equal_yaw(float fparg0, float fparg1, float fparg2)
{
    float var_f13;
    int var_v0;

    var_f13 = fparg1 - fparg0;
    if (var_f13 < 0.0f) {
        var_f13 = -var_f13;
    }
    if (var_f13 > 3.141592502593994140625f) {
        var_f13 = 6.28318500518798828125f - var_f13;
    }
    var_v0 = 1;
    if (!(var_f13 <= fparg2)) {
        var_v0 = 0;
    }
    return var_v0;
}
