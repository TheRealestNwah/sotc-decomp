int GAMEUTIL_is_sign_change(float fparg0, float fparg1)
{
    int var_v0;

    var_v0 = 0;
    if (fparg0 != fparg1) {
        var_v0 = 1;
        if (!((fparg0 * fparg1) <= 0.0f)) {
            var_v0 = 0;
        }
    }
    return var_v0;
}
