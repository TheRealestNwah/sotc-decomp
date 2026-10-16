extern int DldSysUndefSymbol;
extern char *GetCharacterClass(void *);

int SCRConditionMyselfControlModeCheck(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    return p == *(char **)(GetCharacterClass(a) + 0x750);
}
