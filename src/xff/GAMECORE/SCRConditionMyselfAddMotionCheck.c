extern int DldSysUndefSymbol;
extern char *GetCharacterClass(void *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

int SCRConditionMyselfAddMotionCheck(void *a, int b, int c, int d, int e, int f, int g, int i, unsigned int *h)
{
    char *m = *(char **)(GetCharacterClass(a) + 0x30C);
    int n;

    for (n = 0; n < *(int *)(GetCharacterClass(a) + 0x3FC); n++, m += 0x80) {
        if (*(int *)(m + 0x44) == -2)
            continue;
        if (dldResolve(h) == *(char **)(m + 4))
            return 1;
    }
    return 0;
}
