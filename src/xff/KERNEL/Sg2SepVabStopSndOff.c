typedef struct { int a, b, c, vab; char pad[0x40]; } Sep;
extern Sep B_000DD700[];
extern int vab_check_alive(int);
extern void Sg2SepStopSndOff(int);

int Sg2SepVabStopSndOff(int vab)
{
    int i;
    Sep *s;
    if (vab_check_alive(vab)) {
        s = B_000DD700;
        for (i = 0; i < 32; i++, s++) {
            if (s->vab == vab)
                Sg2SepStopSndOff(i);
        }
    }
    return 0;
}
