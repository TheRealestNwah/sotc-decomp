typedef union {
    long l;
    int i[2];
} Flags;

typedef struct {
    char pad0[0x38];
    Flags flags;
    char pad40[4];
    int *done;
    char pad48[0x518];
} AdpcmChannel;

extern AdpcmChannel B_0014E898[];

void adpcmCloseReq(int ch, int *done)
{
    AdpcmChannel *c = &B_0014E898[ch];

    c->done = done;
    if (done != 0) {
        *done = 0;
    }
    c->flags.l |= 0x8000L << 22;
}
