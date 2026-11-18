typedef struct {
    int mod;
    char pad4[0xC - 4];
    int pan;
    char pad10[0x14 - 0x10];
    int vol;
    int velo;
    int note;
    int expr;
    int reverb;
    char pad28[0x30 - 0x28];
    int dumper;
    int bend;
    char pad38[0x40 - 0x38];
    int prog;
    short vph0;
    short vph1;
    int x48;
    char pad4C[0x5C - 0x4C];
    unsigned short ar;
    unsigned short dr;
    unsigned short sr;
    unsigned short rr;
    char pad64[0x68 - 0x64];
    unsigned char *progchunk;
    unsigned char *splitchunk;
} ModChannel;

typedef struct {
    int vab;
    int x4;
    int ssaShift;
    int ssaBase;
    char pad10[0x18 - 0x10];
    int slotClass;
    char pad1C[0x30 - 0x1C];
    int x30;
    int masVolL;
    int masVolR;
    int masPan;
    int x40;
    int masTune;
    char pad48[0x54 - 0x48];
    int lfoCount;
    int lfoBase;
    unsigned short *lfoTbl;
    char pad60[0x2B0 - 0x60];
    ModChannel ch[16];
} ModState;

typedef struct {
    char pad0[0x4C];
    int useVelTbl;
    unsigned char *velTbl;
    char pad54[0x9B0 - 0x54];
} SmfpState;

extern unsigned char *B_000C5C0C;
extern ModState *B_000C5C10;
extern int B_000C5C08;
extern SmfpState B_000C5C18[];
extern int sg2NicoReverbMode;

extern unsigned char *vab_get_seprogchunk(int vab, unsigned int prog);
extern unsigned char *vab_get_splitchunk(unsigned char *p);
extern int vab_get_semastervol(int id);
extern void Sg2SlotVabKeyOffGroup(int vab, int group);
extern void Sg2SlotVabKeyOff(int vab, int ch, int note);
extern int Sg2SlotFreeSearch(int cls);
extern int Sg2SlotSearchParamOlder0(int cls, int type, int a, int b, int c);
extern int Sg2SlotSearchPriority(int cls, int type, int prio);
extern void Sg2SlotSetBasicParam(int a, int i, int b, int c, int d, int e);
extern void Sg2SlotSetGroup(int s, int g);
extern void Sg2SlotSetLoop(int s);
extern void Sg2SlotSetLfoPitchTbl(int s, int table);
extern void Sg2SlotSetBendRange(int s, int r);
extern void Sg2SlotSetBendValue(int s, int v);
extern void Sg2SlotSetLfoPitchSpeed(int s, int v);
extern void Sg2SlotSetLfoPitchDepth(int s, int v);
extern void Sg2SlotSetNoiseOnBit(int hi, int bit);
extern void Sg2SlotSetNoiseOffBit(int hi, int bit);
extern int Sg2RemoteSend(int command, int arg1, int arg2, int arg3);
extern void Sg2SlotSetDumperOn(int s);
extern void Sg2SlotSetReverbOnBit(int hi, int bit);
extern void Sg2SlotSetReverbOffBit(int hi, int bit);
extern int Sg2SlotSetAdsr(int s, unsigned short a, unsigned short b);
extern void Sg2SlotSetMasTune(int s, int v);
extern void Sg2SlotSetPitch(int s, int a, int b, int c, int d, int e);
extern void Sg2SlotSetMasPan(int s, int v);
extern void Sg2SlotSetBasePan(int s, int v);
extern void Sg2SlotSetPan(int s, int v);
extern void Sg2SlotSetVolPhase(int s, int a, int b);
extern void Sg2SlotSetMasVol(int s, int l, int r);
extern void Sg2SlotSetBaseVol(int s, int v);
extern void Sg2SlotSetSeMasVol(int s, int v);
extern void Sg2SlotSetVol(int s, int v);
extern int Sg2SlotSetSsa(int s, int ssa);
extern void Sg2SlotSetKeyOnBit(int hi, int bit);

#ifdef NONMATCHING
/* 12 words differ: v0/v1 swap in the MasTune/Pitch loads and a0/a1 swap in the B_000C5C18[c->mod] index */
static void func_00023DD0(void)
{
    unsigned char *ev = B_000C5C0C;
    int ch = ev[0] & 0xF;
    ModChannel *c;
    unsigned char *pc;
    unsigned char *sp;
    int note;
    int group;
    int slot;
    int lo;
    int lfo;
    unsigned short a1, a2;
    int v;
    long lv;
    unsigned long ul;

    if (ev[2] != 0) {
        ModChannel *c0 = &B_000C5C10->ch[ch];
        c0->mod = B_000C5C08;
        c0->note = ev[1];
        c0->velo = ev[2];
        c0->prog = ev[3];
        c0->progchunk = vab_get_seprogchunk(B_000C5C10->vab, ev[3]);
        c0->splitchunk = vab_get_splitchunk(B_000C5C10->ch[ch].progchunk);
        c = &B_000C5C10->ch[0];
        if (B_000C5C10->x30 == 1)
            return;
        pc = c->progchunk;
        if (pc == 0)
            return;
        sp = c->splitchunk;
        if (sp == 0)
            return;
        note = c->note;
        if (pc[6] - note > 0)
            return;
        sp += (note - pc[6]) * 16;
        c->splitchunk = sp;
        group = sp[0];
        if (group != 0)
            Sg2SlotVabKeyOffGroup(B_000C5C10->vab, group);
        {
            int cls = B_000C5C10->slotClass;
            slot = Sg2SlotFreeSearch(cls);
            if (slot == -1) {
                slot = Sg2SlotSearchParamOlder0(cls, 2, B_000C5C10->x4, c->prog, note);
                if (slot == -1)
                    slot = Sg2SlotSearchPriority(cls, 2, sp[1]);
            }
        }
        Sg2SlotSetBasicParam(2, slot, B_000C5C10->x4, B_000C5C10->vab, c->prog, sp[1]);
        Sg2SlotSetGroup(slot, group);
        if ((unsigned char)(sp[0xF] & 1))
            Sg2SlotSetLoop(slot);
        if (!(sp[0xF] & 0x40))
            lfo = sp[0xE];
        else
            lfo = pc[5];
        if (B_000C5C10->lfoCount > 0)
            Sg2SlotSetLfoPitchTbl(slot, B_000C5C10->lfoBase + B_000C5C10->lfoTbl[lfo]);
        if (sp[0xF] & 0x10)
            Sg2SlotSetBendRange(slot, pc[4]);
        else
            Sg2SlotSetBendRange(slot, sp[0xD]);
        Sg2SlotSetBendValue(slot, c->bend);
        if (sp[0xF] & 0x20) {
            Sg2SlotSetLfoPitchSpeed(slot, 10);
            Sg2SlotSetLfoPitchDepth(slot, 0x7F);
        }
        
        if (sp[0xF] & 2) {
            Sg2SlotSetNoiseOnBit(slot >= 0x18, slot < 0x18 ? 1 << slot : 1 << (slot - 0x18));
            Sg2RemoteSend(5, 0, slot, sp[2]);
        } else {
            Sg2SlotSetNoiseOffBit(slot >= 0x18, slot < 0x18 ? 1 << slot : 1 << (slot - 0x18));
        }
        if (c->dumper != 0)
            Sg2SlotSetDumperOn(slot);
        if (c->reverb == 0x7F && sg2NicoReverbMode != 0)
            Sg2SlotSetReverbOnBit(slot >= 0x18, slot < 0x18 ? 1 << slot : 1 << (slot - 0x18));
        else if ((sp[0xF] & 0x80) && sg2NicoReverbMode != 0)
            Sg2SlotSetReverbOnBit(slot >= 0x18, slot < 0x18 ? 1 << slot : 1 << (slot - 0x18));
        else
            Sg2SlotSetReverbOffBit(slot >= 0x18, slot < 0x18 ? 1 << slot : 1 << (slot - 0x18));
        a1 = *(unsigned short *)(sp + 6);
        if (c->ar != 0)
            a1 = c->ar | (a1 & 0x80FF);
        if (c->dr != 0)
            a1 = c->dr | (a1 & 0xFF0F);
        a2 = *(unsigned short *)(sp + 8);
        if (c->sr != 0)
            a2 = c->sr | (a2 & 0x803F);
        if (c->rr != 0)
            a2 = c->rr | (a2 & 0xFFE0);
        Sg2SlotSetAdsr(slot, a1, a2);
        Sg2SlotSetMasTune(slot, B_000C5C10->masTune);
        Sg2SlotSetPitch(slot, c->note, B_000C5C10->x40, sp[2], (signed char)sp[3], c->x48);
        Sg2SlotSetMasPan(slot, B_000C5C10->masPan);
        v = c->pan;
        if (v >= 0x80)
            v = 0x7F;
        if (v <= 0)
            v = 1;
        Sg2SlotSetBasePan(slot, v);
        v = sp[0xC];
        if (v >= 0x80)
            v = 0x7F;
        if (v <= 0)
            v = 1;
        Sg2SlotSetPan(slot, v);
        Sg2SlotSetVolPhase(slot, c->vph0, c->vph1);
        Sg2SlotSetMasVol(slot, B_000C5C10->masVolL, B_000C5C10->masVolR);
        ul = c->vol;
        ul *= c->expr;
        ul *= c->progchunk[1];
        ul *= sp[0xB];
        Sg2SlotSetBaseVol(slot, ul / 0x1F417F);
        Sg2SlotSetSeMasVol(slot, vab_get_semastervol(B_000C5C10->vab));
        if (B_000C5C18[c->mod].useVelTbl == 0)
            lv = c->velo;
        else
            lv = B_000C5C18[c->mod].velTbl[c->velo];
        Sg2SlotSetVol(slot, lv);
        { unsigned int ssa = *(unsigned short *)(sp + 4); lv = (ssa << B_000C5C10->ssaShift) + B_000C5C10->ssaBase; }
        Sg2SlotSetSsa(slot, lv);
        Sg2SlotSetKeyOnBit(slot >= 0x18, slot < 0x18 ? 1 << slot : 1 << (slot - 0x18));
        return;
    }
    Sg2SlotVabKeyOff(B_000C5C10->vab, ev[3], ev[1]);
}
#endif
