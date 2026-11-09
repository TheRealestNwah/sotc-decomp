typedef struct SepEnt {
    int active;
    int pad4;
    unsigned long lo : 32;
    unsigned long stop : 1;
    unsigned long b33 : 1;
    unsigned long type : 3;
    unsigned long on : 1;
    unsigned long rest : 26;
    int unk10;
    char pad14[0x20];
    int unk34;
    int unk38;
    int unk3C;
    int unk40;
    int unk44;
    char pad48[0x18];
    int tick;
    char pad64[0xC];
} SepEnt;

extern unsigned int WaitSema(int);
extern void SignalSema(int);
extern int B_000C3710;
extern SepEnt B_000C2910[];
extern int soundTickProcCnt;
SepEnt *sndSepReq(int a, int b, int c, int d, void (*init)(SepEnt *), int type, int e10)
{
    SepEnt *e = 0;
    int i;

    WaitSema(B_000C3710);
    for (i = 0; i < 0x20; i++) {
        if (B_000C2910[i].active == 0) {
            goto found;
        }
    }
    goto out;
found:
    e = &B_000C2910[i];
    e->unk34 = a;
    e->unk38 = b;
    e->unk40 = c;
    e->unk44 = d;
    e->unk10 = e10;
    e->stop = 0;
    e->type = type;
    e->on = 1;
    e->unk3C = 0;
    if (init != 0) {
        init(e);
    }
    e->tick = soundTickProcCnt;
    e->active = 1;
out:
    SignalSema(B_000C3710);
    return e;
}
