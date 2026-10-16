extern int DldSysUndefSymbol;
extern void _SCRStartLWS(int, int, int, int);
extern void setGameFlagForGameObj(int);

void SCRFuncStartStageLayoutLWS(void *a, int mode, int flag, int d, int e, int f, unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;

    _SCRStartLWS(*(int *)(p + 0x48), -1, mode, 0);
    if (flag)
        setGameFlagForGameObj(*(int *)(p + 0x48));
}
