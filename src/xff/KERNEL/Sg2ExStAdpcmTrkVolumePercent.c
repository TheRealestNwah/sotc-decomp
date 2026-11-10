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
/* Parked: 22 words differ (loop scheduling around the pinned stream copy in $t0) */
int Sg2ExStAdpcmTrkVolumePercent(Stream *stream0, int trk, int left, int right)
{
    register Stream *stream __asm__("$8") = stream0;
    unsigned long i;
    int n;

    {
        register int off __asm__("$2") = trk * 8;
        register char *base __asm__("$3") = (char *)stream + 0xC;
        register char *q __asm__("$4") = (char *)(off + (int)base);
        __asm__("" : "+r"(q));
        {
            register char *g __asm__("$2") = q;
            __asm__ volatile("" : "+r"(g));
            *(int *)(g + 0x240) = left;
        }
        *(int *)(q + 0x244) = right;
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
