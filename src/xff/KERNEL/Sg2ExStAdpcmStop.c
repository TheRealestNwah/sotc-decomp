typedef struct {
    int state;

    int unknown04;
    unsigned int flags;
    char unknown0C[0x94];
    unsigned long channels;
} Stream;

extern int B_000C5B3C;
extern int B_000C5B40[];
extern int Sg2StAdpcmStop(unsigned long);

static inline unsigned long channelMask(int channel)
{
    return 1UL << channel;
}

int Sg2ExStAdpcmStop(Stream *stream)
{

    unsigned long channel;
    int *available;

    if (!B_000C5B3C) {
        available = B_000C5B40;
        for (channel = 0; channel < 48; ++channel, ++available) {
            if (stream->channels & channelMask((int)channel))
                *available = 1;
        }
    }
    if (stream->state < 16) {
        stream->state = 0;
        return -1;
    }
    stream->state = 0;
    return Sg2StAdpcmStop(stream->channels);
}

