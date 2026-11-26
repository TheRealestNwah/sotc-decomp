#ifndef KERNEL_SG2SLOT_H
#define KERNEL_SG2SLOT_H

/* KERNEL Sg2 sound slots (src/xff/KERNEL/Sg2Slot*.c): the 48 voice slots in
 * B_000DE370, 0xE0 bytes each. Field names follow what the Sg2Slot setters
 * write; xNN fields are not understood yet. */

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
    int flags; /* 1 in use, 4 loop, 8 dumper, 0x200 portamento, 0x400/0x800 LFO pitch/vol */
    int alloc;
    int serial;
    int slotClass;
    int vab;
    int ch;
    int x18;
    int group;
    int x20;
    int note;
    int baseNote;
    int x2C;
    SlotLfo mas;
    SlotMix mix;
    int basePan;
    int pan;
    int x58;
    int bend;
    int ssa;
    int x64;
    int x68;
    int x6C;
    int directPitch;
    short volPhase[2];
    int lfoPitchSpeed;
    int lfoPitchDepth;
    int lfoPitchCount;
    int lfoPitchTbl;
    int lfoPitchCur;
    int lfoPitchEnd;
    unsigned int lfoVolSpeed;
    unsigned int lfoVolDepth;
    int lfoVolCount;
    int lfoVolTbl;
    SlotLfoVol lfoVol;
    SlotTimePan timePan;
    SlotTimePitch timePitch;
    float xC8;
    int poltaStart;
    int poltaCur;
    int poltaTarget;
    float poltaStep;
    int poltaTime;
} Sg2Slot;

extern Sg2Slot B_000DE370[48];

#endif /* KERNEL_SG2SLOT_H */
