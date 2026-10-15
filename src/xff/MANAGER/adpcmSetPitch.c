struct AdpcmChannel {
    char pad00[0x38];
    unsigned long flags;
    char pad40[0x10];
    float volume1;
    char pad54[4];
    float volume0;
    char pad5C[4];
    float pitch0;
    float pitch1;
    char pad68[0x4F8];
};

extern struct AdpcmChannel B_0014E898[];

void adpcmSetPitch(int channel, float pitch0, float pitch1)
{
    struct AdpcmChannel *work = &B_0014E898[channel];
    work->pitch0 = pitch0;
    work->pitch1 = pitch1;
}
