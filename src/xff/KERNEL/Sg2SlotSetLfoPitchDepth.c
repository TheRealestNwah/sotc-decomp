typedef struct {
    int a;
    int b;
    int cur;
    int end;
} SlotLfo;

typedef struct {
    int seMasVol;
    int baseVol;
    int vol;
    int masPan;
} SlotMix;

typedef struct {
    int cur;
    int end;
    float t8;
    float tC;
} SlotLfoVol;

typedef struct {
    int a;
    float t4;
    float t8;
    int c;
} SlotTimePan;

typedef struct {
    float p0;
    float p1;
} SlotTimePitch;

typedef struct {
    int flags;
    int alloc;
    int x8;
    int xC;
    SlotLfo x10;
    char pad20[0x10];
    SlotLfo mas;
    SlotMix mix;
    int basePan;
    int pan;
    int pad58;
    int bend;
    SlotLfo lfo;
    int directPitch;
    short volPhase[2];
    int lfoPitchEnabled;
    int lfoPitchDepth;
    char pad80[0x1C];
    int lfoVolTbl;
    SlotLfoVol lfoVol;
    SlotTimePan timePan;
    SlotTimePitch timePitch;
    char padC8[0x18];
} Sg2Slot;

extern Sg2Slot B_000DE370[];

void Sg2SlotSetLfoPitchDepth(int slot, int depth)
{
    int adjusted;
    if (depth != 0) {
        adjusted = depth;
        if (B_000DE370[slot].alloc == 1)
            adjusted = depth * 2;
    } else {
        adjusted = 0;
    }
    B_000DE370[slot].lfoPitchDepth = adjusted;
    if (depth != 0 && B_000DE370[slot].lfoPitchEnabled != 0)
        B_000DE370[slot].flags |= 0x400;
    else
        B_000DE370[slot].flags &= ~0x400;
}