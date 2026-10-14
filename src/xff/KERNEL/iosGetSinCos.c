extern void iosGetSinCosf(void *, float);

void iosGetSinCos(void *output, int angle)
{
    iosGetSinCosf(output, (float) angle * 0.000000000465660988935301389801679761148989200592041015625f * 3.141592562198638916015625f);
}
