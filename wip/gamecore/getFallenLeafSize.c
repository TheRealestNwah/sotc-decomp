extern int DldSysUndefSymbol;

int getFallenLeafSize(char *obj)
{
    unsigned int *h = (unsigned int *)(obj + 0x1C);
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *p = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
    int count;
    int size = 0x170;

    if (*(int *)(obj + 0x30) != 0)
        count = *(int *)(obj + 0x3C);
    else
        count = *(int *)(obj + 0x28) * *(int *)(obj + 0x2C);
    size += count * 0x80;
    size += *(int *)(p + 8) * 0x40;
    return size;
}
