extern void Sg2DspSetMasterVolume(int core, int l, int r);

void Sg2DspSetMasterVolumeMax(void)
{
    Sg2DspSetMasterVolume(0, 0x3FFF, 0x3FFF);
    Sg2DspSetMasterVolume(1, 0x3FFF, 0x3FFF);
}
