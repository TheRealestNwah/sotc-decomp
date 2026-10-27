static inline void initializeMode(char *s, short sequenceId)
{
    *(int *)(s + 8) = 12;
    *(short *)(s + 0x2A) = sequenceId;
}
void sndSepSetDefaultParam(char *s)
{
    float volume = *(float *)(s + 0x1C);
    int defaultVolume;
    initializeMode(s, -1);
    *(float *)(s + 0x20) = -1.0f;
    defaultVolume = (int)(volume * 127.0f);
    *(float *)(s + 0x24) = 64.0f;
    *(short *)(s + 0x2E) = *(short *)(s + 0x30) = 1;
    *(short *)(s + 0x2C) = 0x1000;
    *(short *)(s + 0x28) = defaultVolume;
}
