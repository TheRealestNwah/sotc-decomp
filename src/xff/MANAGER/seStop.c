extern int sndSepStopReq();

int seStop(char *p)
{
    *(int *)(p + 0x40) = 0;
    return sndSepStopReq(p);
}
