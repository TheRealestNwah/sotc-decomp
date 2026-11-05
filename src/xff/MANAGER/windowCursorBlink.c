typedef struct {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
} Color;

extern int iosGetTCountExtension(void);
extern float iosGetSecondFromTCount(int);
extern float iosGetSinf(float);

void windowCursorBlink(Color *out, Color *in)
{
    float scale = (iosGetSinf(2.0f * (iosGetSecondFromTCount(iosGetTCountExtension()) * 3.14159265f)) + 1.0f) * 0.25f + 0.5f;

    out->r = (unsigned int)(in->r * scale) & 0xFF;
    out->g = (unsigned int)(in->g * scale) & 0xFF;
    out->b = (unsigned int)(in->b * scale) & 0xFF;
    out->a = in->a;
}
