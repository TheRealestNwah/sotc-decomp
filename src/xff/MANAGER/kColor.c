typedef struct {
    char pad0[0x90];
    float r;
    float g;
    float b;
    float a;
    int mode;
} KColorState;

extern KColorState D_001359F0;

void kColor(int mode, float r, float g, float b, float a)
{
    KColorState *k = &D_001359F0;

    k->r = r;
    k->g = g;
    k->b = b;
    k->a = a;
    k->mode = mode;
}
