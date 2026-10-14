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

void adpcmSetPitch(int channel, float pitch0, float pitch1)
{
    struct AdpcmChannel *work = &B_0014E898[channel];
    work->pitch1 = pitch1;
    work->pitch0 = pitch0;
}
