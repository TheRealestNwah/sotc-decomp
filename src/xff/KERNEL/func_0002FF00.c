typedef struct {
    int x0; float b0; float b1; float b2; float a0; float a1; float a2;
    char pad1C[0x2C - 0x1C]; float gain; float freq;
} Shelf;
extern float powf(float, float);
extern float cosf(float);
extern float sinf(float);
extern double sqrt(double);
static void func_0002FF00(Shelf *s)
{
    float A, w, beta;
    A = powf(10.0f, s->gain / 40.0f);
    w = 2.0f * (s->freq / 48000.0f) * 3.1415926f;
    beta = sqrt((A * A + 1.0f) - (A - 1.0f) * (A - 1.0f));
    s->a0 = A * (((A + 1.0f) + (A - 1.0f) * cosf(w)) + beta * sinf(w));
    s->a1 = -2.0f * A * ((A - 1.0f) + (A + 1.0f) * cosf(w));
    s->a2 = A * (((A + 1.0f) + (A - 1.0f) * cosf(w)) - beta * sinf(w));
    s->b0 = ((A + 1.0f) - (A - 1.0f) * cosf(w)) + beta * sinf(w);
    s->b1 = 2.0f * ((A - 1.0f) - (A + 1.0f) * cosf(w));
    s->b2 = ((A + 1.0f) - (A - 1.0f) * cosf(w)) - beta * sinf(w);
}
