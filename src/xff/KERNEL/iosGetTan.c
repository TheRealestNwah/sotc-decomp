extern void iosGetSinCos(float *, int);

float iosGetTan(int a)
{
    float sc[4] __attribute__((aligned(16)));

    iosGetSinCos(sc, a);
    return sc[1] / sc[0];
}
