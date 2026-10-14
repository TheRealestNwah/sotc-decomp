typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
    int i[4];
} Vec4;

typedef struct {
    char pad0[0x1C0];
    int type;
    char pad1C4[0xC];
    Vec4 color;
    Vec4 dir;
    float range;
    float intensity;
} LightClass;

typedef struct {
    char pad0[8];
    unsigned char kind;
    char pad9[0x17];
    LightClass light;
} LightObj;

typedef struct {
    char pad0[0x7C];
    int type;
    Vec4 color;
    Vec4 dir;
    float range;
    float intensity;
} LightData;

extern void InitLayoutObj(LightObj *, LightData *);

int InitLightObj(LightObj *obj, LightData *data)
{
    LightClass *light;

    InitLayoutObj(obj, data);
    light = (obj->kind == 0x13) ? &obj->light : 0;
    light->type = data->type;
    light->color.q = data->color.q;
    light->dir.q = data->dir.q;
    light->range = data->range;
    light->intensity = data->intensity;
    return 1;
}
