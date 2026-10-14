typedef int s128 __attribute__((mode(TI)));
extern float iosCalcFColorToBrightness(int);

void SetColorParamAmbientLight(void *arg0, void *arg1)
{
    float temp_f0;
    float temp_f1;
    float var_f0;

    (*(s128 *)((char *)(arg0) + 0x100)) = (s128) (*(s128 *)((char *)(arg1) + 0));
    (*(float *)((char *)(arg0) + 0x12C)) = (float) (*(float *)((char *)(arg1) + 0x24));
    temp_f0 = iosCalcFColorToBrightness(arg0 + 0x100);
    temp_f1 = (*(float *)((char *)(arg0) + 0x12C));
    (*(float *)((char *)(arg0) + 0x140)) = temp_f0;
    if (temp_f1 < 0.0f) {
        var_f0 = -temp_f1 * temp_f0;
    } else {
        var_f0 = temp_f1 * temp_f0;
    }
    (*(float *)((char *)(arg0) + 0x130)) = var_f0;
}
