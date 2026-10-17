extern float iosCalcFColorToBrightness(float *);

void CalcColorParamDistantLight(void *arg0)
{
    float temp_f0;
    float var_f1;

    temp_f0 = iosCalcFColorToBrightness((float *)((char *)arg0 + 0x10));
    var_f1 = temp_f0 * (*(float *)((char *)(arg0) + 0x24));
    (*(float *)((char *)(arg0) + 0x20)) = temp_f0;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    (*(float *)((char *)(arg0) + 0x28)) = var_f1;
}
