extern int DldSysUndefSymbol;
extern char *GetCharacterClass(int);

static inline char *dldTable(int *h)
{
    int off = *h & 0x3FFFF;

    return off != 0 ? *(char **)((char *)h - off) : 0;
}

static inline char *dldObj(int *h)
{
    char *t = dldTable(h);

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
}

static inline char *dldEntry(int *h)
{
    unsigned int v = *h;
    char *t = dldTable(h);

    return (t != 0 && t != (char *)DldSysUndefSymbol)
               ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC)
               : 0;
}

int SCRConditionGameObjAddMotionCheck(int a, int b, int c, int d, int e, int f, int g, int *h, int *mot)
{
    char *o = dldObj(h);
    char *p;
    int i;

    if (o == 0 || *(int *)(o + 8) == 0 || GetCharacterClass(*(int *)(o + 8)) == 0)
        return 0;
    p = *(char **)(GetCharacterClass(*(int *)(o + 8)) + 0x30C);
    for (i = 0; i < *(int *)(GetCharacterClass(a) + 0x3FC); i++, p += 0x80) {
        if (*(int *)(p + 0x44) != -2 && dldEntry(mot) == *(char **)(p + 4))
            return 1;
    }
    return 0;
}
