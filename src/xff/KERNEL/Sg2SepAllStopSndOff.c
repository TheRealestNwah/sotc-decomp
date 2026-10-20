extern int Sg2SepStopSndOff(unsigned int);

int Sg2SepAllStopSndOff(void)
{
    int i;
    for (i = 0; i < 32; i++)
        Sg2SepStopSndOff(i);
    return 0;
}
