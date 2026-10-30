typedef struct {
    char unknown00[0x44];
    int overMax;
    int underMin;
    char unknown4C[4];
    float result;
    char unknown54[0x14];
    float base;
    char unknown6C[8];
    float unknown74;
    float unknown78;
    char unknown7C[0x28];
    float unknownA4;
    float max;
    float min;
    char unknownB0[0x70];
    float limitMax;
    float limitMin;
} Limiter;

extern float func_0000DEC0(void *, void *, float, float, float, float, float, float, float);

static void func_0000DDC0(Limiter *l, float value)
{
    float base = l->base;
    float max = l->max;
    float min = l->min;
    float result;

    if (l->limitMax < base + max) {
        max = l->limitMax - base;
        if (max < 0)
            max = 0;
    }
    if (base + min < l->limitMin) {
        min = l->limitMin - base;
        if (0 < min)
            min = 0;
    }
    result = func_0000DEC0(&l->unknown4C, l->unknownB0, l->unknown74, l->unknown78, value, l->result, l->unknownA4, max,
                           min);
    l->underMin = 0;
    l->result = result;
    l->overMax = 0;
    if (max - 0.0174532925f <= result)
        l->overMax = 1;
    else if (result <= min + 0.0174532925f)
        l->underMin = 1;
}
