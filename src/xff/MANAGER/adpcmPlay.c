typedef struct {
    char pad0[0x38];
    unsigned long flags;
    char pad40[0xC];
    float volume;
    char pad50[0x230];
    int stream[0xB8];
} AdpcmChannel;
extern AdpcmChannel B_0014E898[];
extern int getSoundMode(void);
extern void Sg2ExStAdpcmSetOutputMode(int *, int);
extern int Sg2ExStAdpcmPlay(int *);

void adpcmPlay(int channel, float volume)
{
    AdpcmChannel *work = &B_0014E898[channel];
    int mode = 2;
    if (getSoundMode() == 0)
        mode = 1;
    Sg2ExStAdpcmSetOutputMode(work->stream, mode);
    Sg2ExStAdpcmPlay(work->stream);
    work->flags |= 0x8000UL << 18;
    work->volume = volume;
    work->flags = (work->flags & ~(3UL << 46)) | ((unsigned long)mode << 46);
}
