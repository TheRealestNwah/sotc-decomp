extern int DldSysUndefSymbol;
extern void isysRequestDeleteObj(void *);

static inline char *dldData(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (char *)t[4] : 0;
}

static inline int dldCount(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != (int *)DldSysUndefSymbol)
        return t[3];
    return 0;
}

void deleteLwsOriDefSeg(char *s)
{
    int i = *(int *)(s + 0xC);
    char *p = *(char **)(s + 0x10);
    while (--i != -1) {
        char *q = dldData((unsigned int *)(p + 0x10));
        int j;
        for (j = dldCount((unsigned int *)(p + 0x10)) - 1; j != -1; j--) {
            if (*(void **)(q + 0x28) != 0) {
                isysRequestDeleteObj(*(void **)(q + 0x28));
                *(void **)(q + 0x28) = 0;
            }
            q += 0x2C;
        }
        p += 0x18;
    }
}
