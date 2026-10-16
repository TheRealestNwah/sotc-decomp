extern int DldSysUndefSymbol;

int GetJudgeVolumeClassWorkSize(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    int n = (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;

    if (n != 0)
        return n * 4 + 0x33;
    return 0;
}
