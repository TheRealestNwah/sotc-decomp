typedef struct { int on; int a; int mod; char pad[0x74]; } Smfp;
extern Smfp B_000E0DC0[];
extern int Sg2SmfpStopSndOff(int);
extern void Sg2ModClose(int);

int Sg2SmfpClose(int i)
{
    Smfp *s;
    if (i >= 0) {
        s = &B_000E0DC0[i];
        if (s->on != 0)
            Sg2SmfpStopSndOff(i);
        Sg2ModClose(s->mod);
        s->on = 0;
    }
    return 0;
}
