extern void iosGetSinCosf(float *sc, float angle);

float iosGetTanf(float angle)
{
    float sc[4] __attribute__((aligned(16)));

    iosGetSinCosf(sc, angle);
    return sc[1] / sc[0];
}
