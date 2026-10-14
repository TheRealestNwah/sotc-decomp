struct AdpcmChannel {
    char pad00[0x38];
    unsigned long flags;
    char pad40[0x10];
    volatile float volume1;
    char pad54[4];
    volatile float volume0;
    char pad5C[4];
    volatile float pitch0;
    volatile float pitch1;
    char pad68[0x4F8];
};

extern struct AdpcmChannel B_0014E898[];

void adpcmSetVol(int channel, float volume0, float volume1)
{
    struct AdpcmChannel *work = &B_0014E898[channel];
    if (!((work->flags >> 39) & 1)) {
        work->volume0 = volume0;
        work->volume1 = volume1;
    }
}
