typedef struct { int on, a, mod, vab; char pad[0x70]; } Smfp;
extern Smfp B_000E0DC0[];
extern int vab_check_alive(int);
extern int Sg2SmfpClose(int);

int Sg2SmfpVabStopSndOff(int vab)
{
    int i;
    Smfp *s;
    if (vab_check_alive(vab)) {
        s = B_000E0DC0;
        for (i = 0; i < 8; i++, s++) {
            if (s->vab == vab)
                Sg2SmfpClose(i);
        }
    }
    return 0;
}
