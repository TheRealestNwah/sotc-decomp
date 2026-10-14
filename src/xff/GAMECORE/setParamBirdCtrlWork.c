typedef struct {
    char pad0[0x80];
    float unk80;
    float unk84;
    float unk88;
    float unk8C;
    float unk90;
    float unk94;
    float unk98;
    float unk9C;
    float unkA0;
    float padA4;
    float unkA8;
} BirdCtrlWork;

void setParamBirdCtrlWork(BirdCtrlWork *w, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j)
{
    w->unk80 = a;
    w->unk84 = b;
    w->unk88 = c;
    w->unk90 = d;
    w->unk94 = e;
    w->unk8C = f;
    w->unk98 = fabsf(g * 0.0174532925f);
    w->unk9C = fabsf(h * 0.0174532925f);
    w->unkA0 = i;
    w->unkA8 = j;
}
