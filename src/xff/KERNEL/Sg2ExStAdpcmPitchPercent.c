typedef struct { int state; char pad[0x2C]; int pitch; char pad2[0x6C]; unsigned long id; char pad3[0x224]; int pct; } St;
extern int Sg2StAdpcmSetPitch(unsigned long, int);

int Sg2ExStAdpcmPitchPercent(St *s, int pct)
{
    s->pct = pct;
    if (s->state < 16)
        return -1;
    return Sg2StAdpcmSetPitch(s->id, s->pitch * pct / 100);
}
