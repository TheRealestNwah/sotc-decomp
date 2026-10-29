extern int Sg2StPcmSetVolume(int, int);
int Sg2ExPcmOutputSetVol(int channel, int volume)
{
    return Sg2StPcmSetVolume(channel, volume);
}
