typedef struct { int on; int a; int mod; char pad[0x74]; } Smfp;
extern Smfp B_000E0DC0[];
extern int Sg2SmfpPause(int, int);
extern int Sg2SmfpCont(int);

int Sg2SmfpStopSndOff(int i)
{
    Smfp *s;
    if (i >= 0) {
        s = &B_000E0DC0[i];
        if (s->on == 2) {
            Sg2SmfpPause(i, 1);
            Sg2SmfpCont(i);
            s->on = 1;
        }
    }
    return 0;
}
