extern float getPlayerHpRatio();

int SCRConditionLessPlayerLife(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!((getPlayerHpRatio() * 100.0f) <= fparg0)) {
        var_v0 = 0;
    }
    return var_v0;
}
