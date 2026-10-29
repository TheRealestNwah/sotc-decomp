extern int Sg2StAdpcmSetPitch(unsigned long, unsigned int);

int Sg2ExStAdpcmCont(int *p)
{
    p[0] = p[1];
    return Sg2StAdpcmSetPitch(*(long *)(p + 0x28), p[0xC]);
}
