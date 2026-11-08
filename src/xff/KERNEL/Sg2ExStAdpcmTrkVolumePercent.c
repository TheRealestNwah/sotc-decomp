typedef struct {
    int left, right;
} VolumePercent;
typedef struct {
    int state;
    char unknown04[0x8];
    VolumePercent vol[80];
} Stream;
#define CHANNELS(s) (*(unsigned long *)((char *)(s) + 0xA0))
extern int func_000205D0(Stream *, int, int);
static inline unsigned long channelMask(int channel)
{
    return 1UL << channel;
}
#ifdef NONMATCHING
/* Parked: 38 words differ (volume slot address is formed as (stream + 0xC) + trk * 8 with stream kept in $t0) */
int Sg2ExStAdpcmTrkVolumePercent(Stream *stream, int trk, int left, int right)
{
    unsigned long i;
    int n;

    {
        VolumePercent *v = stream->vol + trk;
        VolumePercent *w = v;
        w[72].left = left;
        v[72].right = right;
    }
    if (stream->state < 16)
        return -1;
    n = trk;
    for (i = 0; i < 48; ++i) {
        if (CHANNELS(stream) & channelMask((int)i)) {
            if (--trk < 0) {
                func_000205D0(stream, (int)i, n);
                return 0;
            }
        }
    }
    return -1;
}
#endif
