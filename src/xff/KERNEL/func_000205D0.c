typedef struct {
    char unknown00[0x1C];
    int format;
    char unknown20[0x10];
    int left[8];
    int right[8];
} Volume;
typedef struct {
    int unknown00;
    Volume volume;
    char unknown74[0x1CC];
    int percent[8][2];
} Track;
typedef struct {
    int state;
    char unknown04[8];
    Track track;
} Stream;
extern volatile int B_000C5B38;
extern int Sg2StAdpcmSetVolume(unsigned long id, unsigned int l, int r);

static int func_000205D0(Stream *stream, int channel, int index)
{
    int l = stream->track.volume.left[index] * stream->track.percent[index][0] / 100;
    int r = stream->track.volume.right[index] * stream->track.percent[index][1] / 100;

    if (l >= 0x4000)
        l = 0x3FFF;
    if (r >= 0x4000)
        r = 0x3FFF;
    if (B_000C5B38 == 0 || B_000C5B38 == 2) {
        if (r < l)
            r = l;
        else
            l = r;
        if ((B_000C5B38 & 2) && stream->track.volume.format == 0x20000) {
            l /= 2;
            r /= 2;
        }
    }
    return Sg2StAdpcmSetVolume(1UL << channel, l, r);
}
