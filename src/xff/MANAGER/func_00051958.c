extern int DldSysUndefSymbol;
extern void InitAnimationClass(void *, char *);
extern void ResetAnimeFrameTableInfo(void *, char *, char *);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void func_00051958(char *anim, char *src)
{
    char *a;
    char *b;

    InitAnimationClass(anim + 4, src);
    a = dldResolve((unsigned int *)(src + 0x48));
    b = dldResolve((unsigned int *)(src + 0x4C));
    ResetAnimeFrameTableInfo(anim + 0x34, a, b);
    *(int *)(anim + 0x44) = 0;
}
