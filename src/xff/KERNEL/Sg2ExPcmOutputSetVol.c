extern int Sg2StPcmSetVolume();

int Sg2ExPcmOutputSetVol(int a, int b, int c, int d)
{
    return Sg2StPcmSetVolume(a, b, c, d);
}
