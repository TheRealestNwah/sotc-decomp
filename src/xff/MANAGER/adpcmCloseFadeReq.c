typedef union {
    long l;
    int i[2];
} Flags;

typedef struct {
    char pad0[0x38];
    Flags flags;
    char pad40[4];
    int *done;
    char pad48[8];
    float fade_time;
    char pad54[4];
    int fade_count;
    char pad5C[0x504];
} AdpcmChannel;

extern AdpcmChannel B_0014E898[];

void adpcmCloseFadeReq(int ch, int *done, float time)
{
    AdpcmChannel *c = &B_0014E898[ch];

    c->fade_time = time;
    c->fade_count = 0;
    c->flags.l |= 0x8000L << 24;
    c->done = done;
    if (done != 0) {
        *done = 0;
    }
    c->flags.l |= 0x8000L << 22;
}
