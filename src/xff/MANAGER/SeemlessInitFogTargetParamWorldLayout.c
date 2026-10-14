typedef struct {
    int unk0;
    float near;
    float far;
    float min;
    float max;
    float rate;
    int r;
    int g;
    int b;
    int a;
} FogTarget;

typedef struct {
    char pad0[0x20];
    float near;
    float far;
    float min;
    float max;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} WorldLayoutFog;

extern FogTarget B_00147370;
extern int D_00130410;

void SeemlessInitFogTargetParamWorldLayout(WorldLayoutFog *src)
{
    FogTarget *fog = &B_00147370;
    float max;

    fog->near = src->near;
    fog->far = src->far;
    fog->min = src->min;
    max = src->max;
    fog->rate = 1.0f;
    fog->max = max;
    fog->r = src->r;
    fog->g = src->g;
    fog->b = src->b;
    fog->a = src->a;
    D_00130410 = 120;
}
