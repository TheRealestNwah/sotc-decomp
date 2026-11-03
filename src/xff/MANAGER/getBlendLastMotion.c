extern int DldSysUndefSymbol;
static inline char *dldObj(char *handle)
{
    unsigned int encoded = *(unsigned int *)handle;
    int offset = encoded & 0x3FFFF;
    char *table = offset != 0 ? *(char **)(handle - offset) : 0;
    return (table != 0 && table != (char *)DldSysUndefSymbol)
        ? *(char **)(table + 0x10) + (((*(unsigned int *)handle >> 18) & 0xFFF)) * *(int *)(*(char **)(table + 8) + 0xC) : 0;
}
char *getBlendLastMotion(char *handle)
{
    char *entry = dldObj(handle);
    for (;;) { if (dldObj(entry + 12) != 0) entry += 12; else break; }
    return dldObj(entry) + 0x50;
}
