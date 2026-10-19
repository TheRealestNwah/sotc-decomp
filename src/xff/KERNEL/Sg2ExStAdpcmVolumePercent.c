typedef struct {
    int left, right;
} VolumePercent;
typedef struct {
    int state;
    char unknown04[0x9C];
    unsigned long channels;
    char unknownA8[0x1A4];
    VolumePercent percent[8];
} Stream;
extern int func_000205D0(Stream *, int, int);
static inline unsigned long channelMask(int channel)
{
    return 1UL << channel;
}
int Sg2ExStAdpcmVolumePercent(Stream *stream, int percent)
{
    unsigned long i;
    int channel;
    int result = -1;
    VolumePercent *volume = stream->percent;
    for (i = 0; i < 8; ++i, ++volume) {
        volume->right = percent;
        volume->left = percent;
    }
    if (stream->state < 16)
        return -1;
    {
        i = 0;
        channel = 0;
        for (; i < 48; ++i) {
            if (stream->channels & channelMask((int)i)) {
                func_000205D0(stream, (int)i, channel++);
                result = 0;
            }
        }
    }
    return result;
}