extern int DldSysUndefSymbol;
extern void ResetAnimeFrameTableInfo(void *, void *, void *);

static inline char *resolveHandle(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void ResetCharacterClassAnimeFrameTableInfo(char *obj)
{
    char *cls = *(char **)(obj + 0x1C0);

    if (cls != 0)
        ResetAnimeFrameTableInfo(obj + 0x1F0, resolveHandle((unsigned int *)(cls + 0x48)), resolveHandle((unsigned int *)(cls + 0x4C)));
}
