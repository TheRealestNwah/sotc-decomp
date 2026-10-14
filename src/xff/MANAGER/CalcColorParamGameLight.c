typedef struct {
    char pad0[0x20];
    int color;
    float scale;
    char pad28[0x10];
    unsigned char brightness;
    char pad39[3];
    int color_copy;
    float intensity;
} GameLight;

extern unsigned char iosCalcIcolorToBrightness(int);

void CalcColorParamGameLight(GameLight *light)
{
    float f;

    light->color_copy = light->color;
    light->brightness = iosCalcIcolorToBrightness(light->color);
    f = light->brightness * light->scale;
    if (f < 0.0f) {
        f = -f;
    }
    light->intensity = f;
}
