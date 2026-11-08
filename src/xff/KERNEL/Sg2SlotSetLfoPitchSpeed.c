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
    struct {
        int directPitch;
        short volPhase[2];
        int speed;
        int depth;
        int count;
    } lp;
    char pad84[0x18];
    int lfoVolTbl;
    SlotLfoVol lfoVol;
    SlotTimePan timePan;
    SlotTimePitch timePitch;
    char padC8[0x18];
} Sg2Slot;

extern Sg2Slot B_000DE370[];

#ifdef NONMATCHING
/* Parked: 11 words differ (redundant copies of the slot+0x70 address; register allocation) */
void Sg2SlotSetLfoPitchSpeed(int slot, int speed)
{
    if (speed != 0) {
        speed = 0xF0 / (0x3C - speed * 58 / 127);
    }
    B_000DE370[slot].lp.speed = speed;
    B_000DE370[slot].lp.count = 0;
    if (speed != 0 && B_000DE370[slot].lp.depth != 0)
        B_000DE370[slot].flags |= 0x400;
    else
        B_000DE370[slot].flags &= ~0x400;
}
#endif
