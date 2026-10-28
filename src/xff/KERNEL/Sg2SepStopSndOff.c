typedef struct { int status, previous, unk8, vab, mod; char pad14[60]; } Sep;
extern Sep B_000DD700[];
extern int DIntr(void);
extern int EIntr(void);
extern void Sg2ModMidiout1(int, int);
int Sg2SepStopSndOff(unsigned int id)
{
    Sep *sep;
    int enabled;
    if (id < 32) {
        sep = &B_000DD700[id];
        if (sep->status > 0) {
            enabled = DIntr();
            sep->status = 2;
            sep->vab = -1;
            Sg2ModMidiout1(B_000DD700[id].mod, 0xFF);
            Sg2ModMidiout1(B_000DD700[id].mod, 0x41);
            Sg2ModMidiout1(B_000DD700[id].mod, 0xF7);
            if (enabled) {
                EIntr();
            }
        }
    }
    return 0;
}
