extern float getPlayerHpRatio();

int SCRConditionOverPlayerLife(float fparg0)
{
    int var_v0;

    var_v0 = 1;
    if (!(fparg0 <= (getPlayerHpRatio() * 100.0f))) {
        var_v0 = 0;
    }
    return var_v0;
}
