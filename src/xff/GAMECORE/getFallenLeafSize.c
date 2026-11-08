extern int *DldSysUndefSymbol;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

#ifdef NONMATCHING
/* Parked: 11 words differ (register allocation/scheduling); permuter found no zero. */
int getFallenLeafSize(int *obj)
{
    int *res = (int *)dldResolve((unsigned int *)&obj[7]);
    int n = obj[12] != 0 ? obj[15] : obj[11] * obj[10];
    return 0x170 + (n << 7) + (res[2] << 6);
}
#else
int getFallenLeafSize(int *obj);
#endif
