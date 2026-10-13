extern float getPlayerGrip();

int SCRConditionLessPlayerGrip(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(getPlayerGrip() <= fparg0)) {
        var_v0 = 0;
    }
    return var_v0;
}
