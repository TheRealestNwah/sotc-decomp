extern int DldSysUndefSymbol;
static inline char *dldObj(char *handle)
{
    unsigned int encoded = *(unsigned int *)handle;
    int offset = encoded & 0x3FFFF;
    char *table = offset != 0 ? *(char **)(handle - offset) : 0;
    return (table != 0 && table != (char *)DldSysUndefSymbol)
        ? *(char **)(table + 0x10) + (((*(unsigned int *)handle >> 18) & 0xFFF)) * *(int *)(*(char **)(table + 8) + 0xC) : 0;
}
char *getBlendFirstMotion(char *handle)
{
    return dldObj(dldObj(handle)) + 0x50;
}
