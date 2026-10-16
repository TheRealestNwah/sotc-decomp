int *charrootdyn_getSlideCollisionJudgeCBArg(int *out, char *p, int flag)
{
    out[0] = ((*(unsigned int *)(p + 0x68) >> 11) & 1) ? flag != 0 : 0;
    out[1] = (*(unsigned int *)(p + 0x68) >> 15) & 1;
    return out;
}
