extern void ExchangeLWVector(float *, float *);

void bossStatGetBossCloudPos(float *out, float *in)
{
    out[0] = in[1];
    out[1] = in[2];
    out[2] = in[3];
    out[3] = 1.0f;
    ExchangeLWVector(out, out);
}
