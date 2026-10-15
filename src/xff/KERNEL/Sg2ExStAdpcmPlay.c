extern int Sg2StAdpcmPlay(long);
extern void ____VolReflection(int *);
extern void Sg2ExStAdpcmPitchPercent(int *, int);

int Sg2ExStAdpcmPlay(int *s)
{
    int r;
    if (s[0] == 8) {
        s[0] = 0x10;
        r = Sg2StAdpcmPlay(*(long *)(s + 0x28));
        ____VolReflection(s);
        Sg2ExStAdpcmPitchPercent(s, s[0xB3]);
    } else {
        s[2] |= 4;
    }
    return r;
}
