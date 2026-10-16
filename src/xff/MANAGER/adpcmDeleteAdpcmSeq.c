typedef struct {
    char pad[0x38];
    unsigned long flags;
    char pad2[0x520];
} AdpcmSeq;

extern AdpcmSeq B_0014E898[];

void adpcmDeleteAdpcmSeq(int i)
{
    AdpcmSeq *s = &B_0014E898[i];

    s->flags |= 0x8000L << 23;
}
