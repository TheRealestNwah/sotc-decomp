extern float iosGetACosfExact(float);

float GAMEUTIL_get_yaw_by_direction(void *arg0)
{
    float var_f2;

    var_f2 = iosGetACosfExact((*(float *)((char *)(arg0) + 8)));
    if ((*(float *)((char *)(arg0) + 0)) < 0.0f) {
        var_f2 = -var_f2;
    }
    return var_f2;
}
