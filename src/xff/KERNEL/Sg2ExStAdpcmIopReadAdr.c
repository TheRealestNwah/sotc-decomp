typedef struct { char unknown[0xA0]; unsigned long channels; } Stream;
extern int Sg2StAdpcmIopReadAdr(int);
static inline unsigned long channelMask(int channel)
{
    return 1UL << channel;
}
int Sg2ExStAdpcmIopReadAdr(Stream *stream, int track)
{
    unsigned long channel;
    unsigned long channels = stream->channels;
    for (channel = 0; channel < 48; ++channel) {
        if (channels & channelMask((int)channel)) {
            if (--track < 0)
                return Sg2StAdpcmIopReadAdr((int)channel);
        }
    }
    return 0;
}