extern int DldSysUndefSymbol;

int initSkelObjResource(unsigned int *h)
{
    unsigned int v;
    int off;
    char *t, *p;
    if (h == 0)
        return 0;
    v = *h;
    off = v & 0x3FFFF;
    t = off != 0 ? *(char **)((char *)h - off) : 0;
    p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    return *(int *)(p + 8);
}
