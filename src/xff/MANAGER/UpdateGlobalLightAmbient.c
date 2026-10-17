typedef int s128 __attribute__((mode(TI)));
typedef union {s128 q;float f[4];} Color;
extern float iosCalcFColorToBrightness(float *);

void UpdateGlobalLightAmbient(void *light, void *parameter)
{
    float brightness;
    float power;
    float scaled_brightness;

    parameter = (char *)parameter + 0x10;

    ((Color *)((char *)light+0x100))->q=((Color *)parameter)->q;
    (*(float *)((char *)(light) + 0x12C)) = (float) (*(float *)((char *)(parameter) + 0x24));
    brightness = iosCalcFColorToBrightness((float *)((char *)light + 0x100));
    power = (*(float *)((char *)(light) + 0x12C));
    (*(float *)((char *)(light) + 0x140)) = brightness;
    if (power < 0.0f) {
        scaled_brightness = -power * brightness;
    } else {
        scaled_brightness = power * brightness;
    }
    (*(float *)((char *)(light) + 0x130)) = scaled_brightness;
}
