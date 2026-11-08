typedef struct {
    unsigned char buf[0x200];
    int wp;
    char pad[0x7AC];
} MidiOut;

extern MidiOut B_000C5C7C[];
extern int DIntr(void);
extern int EIntr(void);

void Sg2ModMidiout1(int port, unsigned char data)
{
    int intr = DIntr();
    MidiOut *out = &B_000C5C7C[port];

    out->buf[out->wp] = data;
    out->wp = (out->wp + 1) & 0x1FF;
    if (intr) {
        EIntr();
    }
}
