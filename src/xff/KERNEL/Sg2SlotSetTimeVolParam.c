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
    char pad78[0x24];
    int lfoVolTbl;
    SlotLfoVol lfoVol;
    SlotTimePan timePan;
    SlotTimePitch timePitch;
    char padC8[0x18];
} Sg2Slot;

extern Sg2Slot B_000DE370[];

void Sg2SlotSetTimeVolParam(int s, float a, float b)
{
    B_000DE370[s].flags |= 0x20;
    B_000DE370[s].lfoVol.tC = a;
    B_000DE370[s].lfoVol.t8 = b;
}
