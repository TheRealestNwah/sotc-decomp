extern float iosGetACosfExact(float);

float GAMEUTIL_get_pitch_radi(void *arg0)
{
    float var_f2;

    var_f2 = iosGetACosfExact((*(float *)((char *)(arg0) + 8)));
    if ((*(float *)((char *)(arg0) + 4)) < 0.0f) {
        var_f2 = -var_f2;
    }
    if (var_f2 > 1.4835298061370849609375f) {
        var_f2 = 1.4835298061370849609375f;
    } else if (var_f2 < -1.4835298061370849609375f) {
        var_f2 = -1.4835298061370849609375f;
    }
    return var_f2;
}
