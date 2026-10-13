extern float D_0017B058;
extern float D_0017B068;

int bosslifebar_display(void)
{
    int var_v1;

    var_v1 = 0;
    if ((D_0017B068 > 0.0f) || (D_0017B058 > 0.0f)) {
        var_v1 = 1;
    }
    return var_v1;
}
