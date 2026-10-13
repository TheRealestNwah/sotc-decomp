float get_view_angle_lws_anime_mode_base(void *arg0)
{
    float var_f0;
    int var_v1;

    var_v1 = 1;
    if (!((*(float *)((char *)(arg0) + 0x224)) > 0.0f)) {
        var_v1 = 0;
    }
    var_f0 = -1.0f;
    if (var_v1 == 1) {
        var_f0 = (*(float *)((char *)(arg0) + 0x254));
    }
    return var_f0;
}
