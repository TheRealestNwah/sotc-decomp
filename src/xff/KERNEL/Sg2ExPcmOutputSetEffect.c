extern int Sg2StPcmSetEffect();

int Sg2ExPcmOutputSetEffect(int a, int b, int c, int d)
{
    return Sg2StPcmSetEffect(a, b, c, d);
}
