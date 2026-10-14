void sndSepStopReq(char *p)
{
    *(long *)(p + 8) |= 0x100000000L;
}
