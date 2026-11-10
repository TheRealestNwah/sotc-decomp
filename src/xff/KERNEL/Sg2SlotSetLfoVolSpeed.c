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
    char pad80[0x10];
    unsigned int lfoVolSpeed;
    unsigned int lfoVolDepth;
    char pad98[4];
    int lfoVolTbl;
    SlotLfoVol lfoVol;
    SlotTimePan timePan;
    SlotTimePitch timePitch;
    char padC8[0x18];
} Sg2Slot;

extern Sg2Slot B_000DE370[];

/* Parked: 44 words differ (the dpcmp call and unsigned-to-float conversion miss their delay slots, shifting the tail by one word). */
#ifdef NONMATCHING
void Sg2SlotSetLfoVolSpeed(int slot, int val)
{
    float f;
    if (val != 0) {
        f = val;
        f = f / 6.35f;
    } else
        f = 0.0f;
    B_000DE370[slot].lfoVolSpeed = f;
    if (f != 0.0 && (float)B_000DE370[slot].lfoVolDepth != 0.0f)
        B_000DE370[slot].flags |= 0x800;
    else
        B_000DE370[slot].flags &= ~0x800;
}
#else
extern void Sg2SlotSetLfoVolSpeed(int slot, int val);
#endif
