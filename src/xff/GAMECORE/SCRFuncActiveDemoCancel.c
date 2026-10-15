extern int DldSysUndefSymbol;
extern void activeDemoCancel(char *);

void SCRFuncActiveDemoCancel(void *a, int b, int c, int d, int e, int g, unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    activeDemoCancel((t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0);
}
