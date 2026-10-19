typedef struct {
    int state;
    char unknown04[0x7C];
    int dsp[8];
    unsigned long channels;
} Stream;
extern void Sg2SlotSetReverbOffBit(int, int);
extern void Sg2SlotSetReverbOnBit(int, int);
static inline unsigned long channelMask(int channel)
{
    return 1UL << channel;
}
static inline int coreForChannel(unsigned long channel)
{
    return !(channel < 24);
}
static inline int bitForChannel(unsigned long channel)
{
    if (channel < 24)
        return 1 << (int)channel;
    return 1 << (int)(channel - 24);
}
int Sg2ExStAdpcmTrkDspSw(Stream *stream, int track, int enabled)
{
    unsigned long channels;
    unsigned long channel;
    if (stream->state < 16)
        return -1;
    channels = stream->channels;
    if (enabled == -1)
        enabled = stream->dsp[track];
    for (channel = 0; channel < 48; ++channel) {
        if (channels & channelMask((int)channel)) {
            if (--track >= 0)
                continue;
            switch (enabled) {
            case 0:
                Sg2SlotSetReverbOffBit(coreForChannel(channel), bitForChannel(channel));
                return 0;
            case 1:
                Sg2SlotSetReverbOnBit(coreForChannel(channel), bitForChannel(channel));
                return 0;
            }
            return 0;
        }
    }
    return -1;
}