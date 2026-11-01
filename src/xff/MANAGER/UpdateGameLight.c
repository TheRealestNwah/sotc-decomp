typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} Vector;

typedef struct GameLight GameLight;

struct GameLight {
    Vector pos;
    Vector dir;
    unsigned char rgba[4];
    float scale;
    float range;
    char p2C[8];
    float rangeSq;
    unsigned char brightness;
    char p39[3];
    int colorCopy;
    float intensity;
    char p44[0x10];
    void (*func)(GameLight *);
};

typedef struct {
    Vector pos;
    Vector dir;
    float scale;
    float range;
    float color[3];
} GameLightParam;

extern unsigned char iosCalcIcolorToBrightness(int);

void UpdateGameLight(GameLight *light, char *src)
{
    GameLightParam *p = (GameLightParam *)(src + 0x10);
    float f;

    light->pos.q = p->pos.q;
    light->dir.q = p->dir.q;
    light->rgba[0] = (unsigned int)p->color[0];
    light->rgba[1] = (unsigned int)p->color[1];
    light->rgba[2] = (unsigned int)p->color[2];
    light->rgba[3] = 0xFF;
    light->scale = p->scale;
    light->range = p->range;
    if (light->func != 0) {
        light->func(light);
    }
    light->colorCopy = *(int *)light->rgba;
    light->brightness = iosCalcIcolorToBrightness(*(int *)light->rgba);
    f = light->brightness * light->scale;
    if (f < 0.0f) {
        f = -f;
    }
    light->intensity = f;
    light->rangeSq = light->range * light->range;
}
