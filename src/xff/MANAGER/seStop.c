extern void sndSepStopReq(char *);

void seStop(char *object)
{
    *(int *)(object + 0x40) = 0;
    sndSepStopReq(object);
}
