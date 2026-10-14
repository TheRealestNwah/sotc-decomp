typedef union {
    float f;
    int i;
} Word;

typedef struct {
    char pad0[0x4E];
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char pad51[7];
    float near;
    float far;
    float density;
    float min;
    float max;
} FogColClass;

extern FogColClass B_00148A40;

void SetInitFogColClassFromStageData(Word *data)
{
    FogColClass *fog = &B_00148A40;

    fog->near = data[1].f;
    fog->far = data[2].f;
    fog->min = data[3].f;
    fog->max = data[4].f;
    fog->density = data[6].i;
    fog->r = data[7].i;
    fog->g = data[8].i;
    fog->b = data[9].i;
}
