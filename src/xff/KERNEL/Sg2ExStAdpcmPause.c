extern int Sg2StAdpcmSetPitch(long, int);

int Sg2ExStAdpcmPause(int *p)
{
    int s = p[0];
    if (s == 0x80)
        return -1;
    p[1] = s;
    p[0] = 0x80;
    return Sg2StAdpcmSetPitch(*(long *)(p + 40), 0);
}
