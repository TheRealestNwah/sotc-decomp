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

typedef struct { unsigned int v; char pad[0xDC]; } VolLfoField;
extern Sg2Slot B_000DE370[];
extern VolLfoField B_000DE400[];

/* Parked: ~71 words differ; the float conversion and flag test schedule differently from the original. */
#ifdef NONMATCHING
void Sg2SlotSetLfoVolSpeed(int slot, int val)
{
    float f;
    if (val != 0)
        f = val / 6.35f;
    else
        f = 0.0f;
    B_000DE400[slot].v = f;
    if (f != 0.0 && (float)*(unsigned int *)((char *)&B_000DE370[slot] + 0x94) != 0.0f)
        B_000DE370[slot].flags |= 0x800;
    else
        B_000DE370[slot].flags &= ~0x800;
}
#else
extern void Sg2SlotSetLfoVolSpeed(int slot, int val);
#endif
