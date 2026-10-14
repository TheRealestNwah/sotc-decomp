

void sndSepSetPan(void *arg0, float fparg0) {
    float var_f0;
    float var_f12;

    var_f12 = fparg0;
    var_f0 = 1.0f;
    if ((var_f12 > 1.0f) || (var_f0 = -1.0f, (var_f12 < -1.0f))) {
        var_f12 = var_f0;
    }
    (*(float *)((char *)(arg0) + 0x24)) = (float) (int) ((var_f12 * 63.0f) + 64.0f);
}
