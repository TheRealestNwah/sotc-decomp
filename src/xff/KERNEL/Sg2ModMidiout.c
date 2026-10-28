typedef struct {
    unsigned char buf[0x200];
    int wp;
    char pad[0x7AC];
} MidiOut;

extern MidiOut B_000C5C7C[];
extern int DIntr(void);
extern int EIntr(void);
extern void *memcpy(void *, const void *, unsigned int);

void Sg2ModMidiout(int port, int size, unsigned char *data)
{
    int intr = DIntr();
    MidiOut *out = &B_000C5C7C[port];
    int space = 0x200 - out->wp;
    int rest = space - size;

    if (rest >= 0) {
        memcpy(out->buf + out->wp, data, size);
        out->wp = (out->wp + size) & 0x1FF;
    } else {
        memcpy(out->buf + out->wp, data, space);
        memcpy(out->buf, data + space, -rest);
        out->wp = -rest;
    }
    if (intr) {
        EIntr();
    }
}
