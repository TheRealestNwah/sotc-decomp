int GAMEUTIL_is_max_input(float fparg0, float fparg1)
{
    int var_v0;

    var_v0 = 1;
    if (!(((fparg0 * fparg0) + (fparg1 * fparg1)) > 0.98999995f)) {
        var_v0 = 0;
    }
    return var_v0;
}
