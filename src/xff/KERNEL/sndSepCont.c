void sndSepCont(char *p)
{
    *(long *)(p + 8) &= ~0x200000000L;
}
