extern int DldSysUndefSymbol;
extern char *GetLayoutClass(void *);
extern void _gameFlagCls(int);

void SCRResetMyOwnGameFlag(void *a)
{
    unsigned int *h = (unsigned int *)(*(char **)(GetLayoutClass(a) + 0x1A4) + 0x10);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    if (p != 0)
        _gameFlagCls(*(int *)(p + 8));
}
