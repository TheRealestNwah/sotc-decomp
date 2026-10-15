extern int DldSysUndefSymbol;

int getArrowWaterSize(char *a)
{
    unsigned int *h = (unsigned int *)(a + 0x1C);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    return (*(int *)(p + 8) << 6) + 0xDF0;
}
