extern void iosGetSinCosf(float *, float);

void iosGetAlignSinCosf(float *out, float a)
{
    float t[4] __attribute__((aligned(16)));
    iosGetSinCosf(t, a);
    out[0] = t[1];
    out[1] = t[0];
}
