typedef struct {
    char pad0[0x90];
    union {
        struct {
            float r, g, b, a;
        } fields;
        float values[4];
    } color;
} GlState;

extern GlState D_00130480;

void glColor3f(float r, float g, float b)
{
    GlState *gl = &D_00130480;
    float *color;
    float value;
    int remaining = 3;
    float maximum;

    gl->color.fields.r = r * 255.0f;
    gl->color.fields.g = g * 255.0f;
    gl->color.fields.b = b * 255.0f;
    maximum = 255.0f;
    gl->color.fields.a = 128.0f;
    color = gl->color.values;
    do {
        value = *color;
        if (value > maximum) {
            *color = maximum;
            value = maximum;
        }
        if (value < 0.0f) {
            *color = 0.0f;
        }
        remaining--;
        color++;
    } while (remaining >= 0);
}
