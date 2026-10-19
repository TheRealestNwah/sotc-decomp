typedef struct {
    int state;
    int unknown04;
    unsigned int flags;
    char unknown0C[0x94];
    unsigned long channels;
} Stream;
extern int Sg2ExStAdpcmStop(Stream *);
extern int Sg2StAdpcmClose(int);
extern int B_000C5B40[];
typedef int (*StreamSignal)(void *, int, int, int);
extern StreamSignal B_000C5C00;
static inline unsigned long channelMask(int channel)
{
    return 1UL << channel;
}
int Sg2ExStAdpcmClose(Stream *stream)
{
    int result = -1;
    unsigned long channel;
    int *available;
    if (stream->state >= 16)
        Sg2ExStAdpcmStop(stream);
    stream->state = 0;
    available = B_000C5B40;
    for (channel = 0; channel < 48; ++channel, ++available) {
        if (stream->channels & channelMask((int)channel)) {
            result = 0;
            Sg2StAdpcmClose((int)channel);
            *available = 1;
        }
    }
    if (!(stream->flags & 2))
        B_000C5C00(stream, 4, 0, 0);
    return result;
}