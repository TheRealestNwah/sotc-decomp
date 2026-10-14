float GameLightCalcImpact(void *arg0, float fparg0)
{
    float var_f0;

    var_f0 = (*(float *)((char *)(arg0) + 0x40)) * (1.0f - (fparg0 / (*(float *)((char *)(arg0) + 0x28))));
    if (var_f0 < 0.0f) {
        var_f0 = -var_f0;
    }
    return var_f0;
}
