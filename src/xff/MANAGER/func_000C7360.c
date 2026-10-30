typedef int s128 __attribute__((mode(TI)));
extern float glSetFogFactor(s128 *);
extern void glSetFogFactorDirect(int);

static void func_000C7360(char *a, char *b)
{
    s128 v = *(s128 *)(a + 0x10);
    float f = glSetFogFactor(&v);
    glSetFogFactorDirect(255 - (int)((255.0f - f) * *(float *)(b + 0x24)));
}
