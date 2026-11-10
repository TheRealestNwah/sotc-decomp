typedef struct {
    int owner;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    char pad18[8];
    int unk20;
    int unk24;
    int unk28;
    int unk2C;
    int unk30;
    int unk34;
    int unk38;
    int unk3C;
    int unk40;
    short unk44;
    short unk46;
    int unk48;
    int unk4C;
    int unk50;
    int unk54;
    int unk58;
    short unk5C;
    short unk5E;
    short unk60;
    short unk62;
    char unk64;
    char unk65;
    char unk66;
    char unk67;
    int unk68;
    int unk6C;
} SqCh;

typedef struct {
    int unk0;
    char pad4[0xC];
    int unk10;
    int unk14;
    char pad18[4];
    int unk1C;
    int unk20;
    int unk24;
    int unk28;
    int unk2C;
    int unk30;
    int unk34;
    int unk38;
    int unk3C;
    int unk40;
    int unk44;
    char pad48[0x18];
    int unk60;
    char unk64;
    char pad65[0x247];
    int unk2AC;
    SqCh ch[16];
    char pad9B0[0x9B0 - 0x2B0 - 16 * 0x70];
} SqPlayer;

extern SqPlayer B_000C5C18[];

#ifdef NONMATCHING
/* Parked: 65 words differ (register allocation and scheduling); permuter
 * stalled around 1300. */
static void func_00021488(int n)
{
    SqPlayer *p = &B_000C5C18[n];
    SqCh *c;
    int i;

    p->unk64 = -0x80;
    p->unk14 = 1;
    p->unk38 = 0x7F;
    p->unk44 = 0x1000;
    p->unk30 = 0;
    p->unk2AC = 1;
    p->unk34 = 0x7F;
    p->unk2C = 0;
    p->unk24 = 0;
    p->unk28 = 0;
    p->unk1C = 0;
    p->unk20 = 0;
    p->unk40 = 0;
    p->unk60 = 0;
    p->unk10 = 0;
    p->unk3C = 0x40;
    p->unk0 = -1;
    c = p->ch;
    for (i = 0; i < 16; i++) {
        int one = 1; int drum = (i == 9) ? one : 0;
        c->owner = n;
        c->unk4 = 0;
        c->unk2C = 1 - drum;
        c->unk8 = 0xFF;
        c->unkC = 0x40;
        c->unk10 = 0;
        c->unk14 = 0x7F;
        c->unk20 = 0x7F;
        c->unk24 = 0;
        c->unk30 = 0;
        c->unk34 = 0x40;
        c->unk64 = 0;
        c->unk65 = 0;
        c->unk66 = 0;
        c->unk67 = 0;
        c->unk48 = 0x1000;
        c->unk68 = 0;
        c->unk6C = 0;
        c->unk5C = 0;
        c->unk5E = 0;
        c->unk60 = 0;
        c->unk62 = 0;
        c->unk4C = 0;
        c->unk50 = 0;
        c->unk54 = 0;
        c->unk58 = 0;
        c->unk38 = 0;
        c->unk3C = 0;
        c->unk46 = 1;
        c->unk44 = 1;
        c->unk28 = drum;
        c++;
    }
}
#endif
