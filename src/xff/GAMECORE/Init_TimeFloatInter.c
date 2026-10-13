typedef struct {
    float f0;
    float f4;
    float f8;
    float fC;
    float f10;
} TimeFloatInter;

void Init_TimeFloatInter(TimeFloatInter *t, float a, float b, float c, float d)
{
    t->f0 = c;
    t->f4 = b;
    t->f8 = a;
    t->fC = b;
    t->f10 = d;
}
