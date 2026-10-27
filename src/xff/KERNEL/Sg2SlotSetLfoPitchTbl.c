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
    SlotLfo pitchPlayback;
    char pad90[0xC];
    int lfoVolTbl;
    SlotLfoVol lfoVol;
    SlotTimePan timePan;
    SlotTimePitch timePitch;
    char padC8[0x18];
} Sg2Slot;

extern Sg2Slot B_000DE370[];

static inline void setTable(Sg2Slot *slot, int table)
{
    slot->pitchPlayback.b = table;
}

void Sg2SlotSetLfoPitchTbl(int slot, int table)
{
    if (table != 0) {
        setTable(&B_000DE370[slot], table);
        B_000DE370[slot].pitchPlayback.cur = table;
        B_000DE370[slot].pitchPlayback.end = table + 0x3C;
    }
}