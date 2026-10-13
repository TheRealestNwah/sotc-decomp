extern float D_0017A304;

void setPlayerO2(float fparg0)
{
    float var_f0;

    var_f0 = 100.0f;
    if (!(fparg0 > 100.0f)) {
        var_f0 = 0.0f;
        if (!(fparg0 < 0.0f)) {
            var_f0 = fparg0;
        }
    }
    D_0017A304 = var_f0;
}
