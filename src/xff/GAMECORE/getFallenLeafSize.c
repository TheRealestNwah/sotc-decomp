extern int *DldSysUndefSymbol;

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

int getFallenLeafSize(int *obj)
{
    int *res = (int *)dldResolve((unsigned int *)&obj[7]);
    register int base __asm__("$5");
    int n;
    base = 0x170;
    n = obj[12] != 0 ? obj[15] : obj[10] * obj[11];
    base = (n << 7) + base;
    __asm__ volatile("" : "+r"(base));
    return base + (res[2] << 6);
}
