extern float getPlayerGrip();

int SCRConditionOverPlayerGrip(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 <= getPlayerGrip())) {
        var_v0 = 0;
    }
    return var_v0;
}
