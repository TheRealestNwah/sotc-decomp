typedef struct {
    int state;
    char unknown04[0x9C];
    unsigned long channels;
} Stream;
extern int func_000205D0(Stream *, int, int);
static inline unsigned long channelMask(int channel)
{
    return 1UL << channel;
}
static void ____VolReflection(Stream *stream)
{
    unsigned long i;
    int channel;

    if (stream->state < 16)
        return;
    i = 0;
    channel = 0;
    for (; i < 48; ++i) {
        if (stream->channels & channelMask((int)i))
            func_000205D0(stream, (int)i, channel++);
    }
}
