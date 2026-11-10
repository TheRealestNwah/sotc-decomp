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
/* Parked: 4 words differ (slot*7 lands in $v1 not $a1; base materialized via $v1 instead of lui $v0/addiu $v1) */
void Sg2SlotSetLfoPitchSpeed(int slot, int speed)
{
    int off = slot * (int)sizeof(Sg2Slot);
    register int offc __asm__("$9") = off;
    register int o70 __asm__("$7");
    __asm__("" : "+r"(offc));
    o70 = offc + 0x70;
    __asm__("" : "+r"(o70));
    if (speed != 0) {
        speed = 0xF0 / (0x3C - speed * 58 / 127);
    }
    {
        register char *base __asm__("$3") = (char *)B_000DE370;
        register char *bc __asm__("$4") = base;
        register Sg2Slot *fe __asm__("$5");
        register int *lp __asm__("$8");
        __asm__("" : "+r"(bc));
        fe = (Sg2Slot *)(off + base);
        lp = (int *)(bc + o70);
        __asm__("" : "+r"(lp));
        {
            register int *l2 __asm__("$2") = lp;
            register int *l3 __asm__("$3");
            __asm__("" : "+r"(l2));
            l3 = l2;
            __asm__("" : "+r"(l3));
            l2[2] = speed;
            l3[4] = 0;
            if (speed != 0 && lp[3] != 0) {
                register Sg2Slot *fs __asm__("$3") = (Sg2Slot *)(offc + (int)bc);
                fs->flags |= 0x400;
                return;
            }
        }
        fe->flags &= ~0x400;
    }
}
#endif
